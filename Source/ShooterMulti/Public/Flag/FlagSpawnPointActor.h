// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlagSpawnPointActor.generated.h"

UCLASS()
class SHOOTERMULTI_API AFlagSpawnPointActor : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	static TArray<FVector>* spawnPointsPosition;
public:	
	// Sets default values for this actor's properties
	AFlagSpawnPointActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
