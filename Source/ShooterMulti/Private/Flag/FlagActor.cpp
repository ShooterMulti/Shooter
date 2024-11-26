// Fill out your copyright notice in the Description page of Project Settings.
#include "Flag/FlagActor.h"

#include "Flag/FlagSpawnPointActor.h"
#include "Math/UnrealMathUtility.h"

#include "Game/ShooterMultiGameMode.h"
#include "Game/ShooterMultiGameState.h"

// Sets default values
AFlagActor::AFlagActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AFlagActor::GetLifetimeReplicatedProps( TArray< class FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME( AFlagActor, m_spawnLocation );
}

// Called when the game starts or when spawned
void AFlagActor::BeginPlay()
{
	Super::BeginPlay();
	bReplicates = true;

	m_gameState = static_cast<AShooterMultiGameState*>(GetWorld()->GetGameState());

	InitServer(); // is only called on server

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	// SetActorTickEnabled(false);
}

void AFlagActor::InitServer()
{
	// is only called on server
	if(!HasAuthority())
	{
		return;
	}

	m_gameState->m_flagLife = maxLife;
}

#include "Game/ShooterMultiGameMode.h"

// Called every frame
void AFlagActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(flagDebug)
	{
		static_cast<AShooterMultiGameMode*>(GetWorld()->GetAuthGameMode())->MatchInit();
		flagDebug = false;
	}
}

void AFlagActor::ChooseSpawnLocation()
{
	// is only called on server
	if(!HasAuthority())
	{
		return;
	}

	m_spawnLocation = (*AFlagSpawnPointActor::spawnPointsPosition)[FMath::RandRange(0, AFlagSpawnPointActor::spawnPointsPosition->Num() - 1)];
}

void AFlagActor::Spawn()
{
	SetActorLocation(m_spawnLocation);

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void AFlagActor::OnHit(ETeam _team, int _damage)
{
	if(HasAuthority())
	{
		return;
	}

	if(_team == ETeam::None)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("ERROR no team detected"))); // TODELETE
		//TODO uncomment the line
		// return; //XXX if no team detected it will return and the flag will not be damaged but it is not supposed to happen.
	}

	m_gameState->m_flagLife--;
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString::Printf(TEXT("Flag Life: %d"), m_gameState->GetFlagLife())); // TODELETE
	
	
}