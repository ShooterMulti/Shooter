// Fill out your copyright notice in the Description page of Project Settings.


#include "Flag/FlagSpawnPointActor.h"

TArray<FVector>* AFlagSpawnPointActor::spawnPointsPosition = nullptr;

// Sets default values
AFlagSpawnPointActor::AFlagSpawnPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AFlagSpawnPointActor::BeginPlay()
{
	Super::BeginPlay();

	if (!spawnPointsPosition)
	{
		spawnPointsPosition = new TArray<FVector>();
	}

	AFlagSpawnPointActor::spawnPointsPosition->Add(GetActorLocation());
	//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Black, FString::Printf(TEXT("Actor spawned: %d"), AFlagSpawnPointActor::spawnPointsPosition->Num())); // TODELETE
}

void AFlagSpawnPointActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (spawnPointsPosition)
	{
		delete spawnPointsPosition;
		spawnPointsPosition = nullptr;
	}
}