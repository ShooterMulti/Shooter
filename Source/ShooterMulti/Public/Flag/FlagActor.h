// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "FlagActor.generated.h"

enum ETeam;
class AShooterMultiGameState;

UCLASS()
class SHOOTERMULTI_API AFlagActor : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag_Values")
	int maxLife = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "debug")
    bool flagDebug = false;

	// Sets default values for this actor's properties
	AFlagActor();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps( TArray< class FLifetimeProperty > & OutLifetimeProps ) const override;

	// UFUNCTION()    
    void OnHit(ETeam _team, int _damage = 0);

	void Spawn();
	// /!\ Server Function ONLY
	void ChooseSpawnLocation();

protected:
	virtual void BeginPlay() override;

	// /!\ Server Function ONLY
	void InitServer();
private:
	UPROPERTY(Replicated)
	FVector m_spawnLocation;

	AShooterMultiGameState* m_gameState = nullptr;
};
