#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterMultiGameModeLobby.generated.h"


UCLASS()
class SHOOTERMULTI_API AShooterMultiGameModeLobby : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterMultiGameModeLobby();

	virtual void BeginPlay() override;
};
