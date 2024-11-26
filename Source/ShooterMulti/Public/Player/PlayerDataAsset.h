// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "PlayerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERMULTI_API UPlayerDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 PlayerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 PlayerSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	int32 PlayerJumpHeight;
};
