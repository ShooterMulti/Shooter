// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Game/ShooterMultiPlayerState.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UBoxComponent;

struct FInputActionValue;

UCLASS()
class SHOOTERMULTI_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	TObjectPtr<AShooterMultiPlayerState> playerState;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> springArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> cameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TObjectPtr<UBoxComponent> headBoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TSubclassOf<AActor> projectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public :
	// Actions Input Functions
	void Move(const FInputActionValue& _value);

	void Look(const FInputActionValue& _value);

	void Jump();

	void Dash(float walkSpeed);

	void Fire();

	void Reload();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerAttackAnimMontage();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayOnhitAnimMontage();

	UFUNCTION(BlueprintCallable)
	void OnHitWithDamage(int damage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_FiringStateChanged)
	bool isFiring = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_OnhitEvent)
	bool isOnhit = false;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	// Input Mapping Context
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> defaultMapping;

	UFUNCTION()
	void OnRep_FiringStateChanged();

	UFUNCTION()
	void OnRep_OnhitEvent();

	UFUNCTION(Server, Reliable)
	void ServerFire();

	UFUNCTION(Server, Reliable)
	void ServerOnHit();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
