// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/Weapon/Projectile.h"
#include "GameFramework/SpringArmComponent.h"

#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Camera components
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	springArmComponent->SetupAttachment(RootComponent);
	springArmComponent->TargetArmLength = 500.0f;
	springArmComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	cameraComponent->SetupAttachment(springArmComponent, USpringArmComponent::SocketName);

	// Lock the camera to the character
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationRoll = false;
	//bUseControllerRotationYaw = false;

	// Only the camera boom should rotate	
	springArmComponent->bUsePawnControlRotation = true;
	cameraComponent->bUsePawnControlRotation = false;

	headBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HeadBoxCollision"));
	headBoxCollision->SetupAttachment(GetMesh(), TEXT("head"));

	headBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	headBoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	headBoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	// Default Camera FOV
	//targetFOV = 90.f;
	//currentFOV = 90.f;
	//focusSpeed = 0.3f;
	bReplicates = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (const TObjectPtr<ULocalPlayer> Player = (GEngine && GetWorld()) ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr)
	{
		TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		if (defaultMapping)
		{
			Subsystem->AddMappingContext(defaultMapping, 0);
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	FVector2D moveVector = value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, moveVector.X);
		AddMovementInput(RightDirection, moveVector.Y);
	}
}

void APlayerCharacter::Look(const FInputActionValue& value)
{
	FVector2D lookVector = value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(-lookVector.X);
		AddControllerPitchInput(lookVector.Y);
	}
}

void APlayerCharacter::Jump()
{
	ACharacter::Jump();
}

void APlayerCharacter::Dash(float walkSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void APlayerCharacter::Fire()
{
	PlayerAttackAnimMontage();

	FName MuzzleSocketName = TEXT("Muzzle_01");
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);
	if (USkeletalMeshComponent* SkeletalMesh = GetMesh())
	{
		FVector MuzzleLocation = SkeletalMesh->GetSocketLocation(MuzzleSocketName);
		FRotator MuzzleRotation = SkeletalMesh->GetSocketRotation(MuzzleSocketName);

		if (projectileClass)
		{
			GetWorld()->SpawnActor<AProjectile>(projectileClass, MuzzleLocation, CameraRotation)->SetProjectileTeam(playerState->team);
		}
	}

	// Make camera shake


	isFiring = !isFiring;

	if (!HasAuthority())
	{
		ServerFire();
		return;
	}
}

void APlayerCharacter::Reload()
{
}

void APlayerCharacter::OnHitWithDamage(int damage)
{
	if (playerState)
	{
		playerState->life -= damage;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerState is null"));
	}
}	

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, isFiring);
	DOREPLIFETIME(APlayerCharacter, isOnhit);
}

void APlayerCharacter::OnRep_FiringStateChanged()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("caca"));
	PlayerAttackAnimMontage();
	// Spawn Projectile bullet

	// Get the camera transform
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	// Offset the spawn location
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(FVector(100.0f, 0.0f, 0.0f));

	// Spawn the projectile
	if (projectileClass)
	{
		GetWorld()->SpawnActor<AProjectile>(projectileClass, MuzzleLocation, CameraRotation);
	}
}

void APlayerCharacter::OnRep_OnhitEvent()
{
	isOnhit = !isOnhit;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!playerState)
	{
		playerState = Cast<AShooterMultiPlayerState>(GetPlayerState());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PlayerState initialized successfully"));
	}
	if (GetVelocity().Size() > 0.f && GetCharacterMovement()->IsMovingOnGround())
	{
		const float WalkCycleSpeed = 15.0f;  
		const float WalkCycleHeight = 15.0f; 

		const float Time = GetWorld()->GetTimeSeconds();
		float VerticalOffset = FMath::Sin(Time * WalkCycleSpeed) * WalkCycleHeight;

		FVector NewLocation = springArmComponent->GetRelativeLocation();
		NewLocation.Z = VerticalOffset;

		springArmComponent->SetRelativeLocation(NewLocation);
	}
	else
	{
		FVector NewLocation = springArmComponent->GetRelativeLocation();
		NewLocation.Z = 0.0f;
		springArmComponent->SetRelativeLocation(NewLocation);
	}
	if (HasAuthority() && playerState)
	{
		if(playerState->life <= 0)
			Destroy();
	}
}

void APlayerCharacter::ServerFire_Implementation()
{
	Fire();
}

void APlayerCharacter::ServerOnHit_Implementation()
{
	PlayOnhitAnimMontage();
}