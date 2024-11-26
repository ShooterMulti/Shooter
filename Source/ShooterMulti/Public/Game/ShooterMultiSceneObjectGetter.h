// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterMultiSceneObjectGetter.generated.h"

UCLASS()
class SHOOTERMULTI_API AShooterMultiSceneObjectGetter : public AActor
{
	GENERATED_BODY()

private:
	static AShooterMultiSceneObjectGetter* m_instance;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SceneObjects")
	class AFlagActor* flag;

	AShooterMultiSceneObjectGetter();
	static AShooterMultiSceneObjectGetter* GetInstance();

};
