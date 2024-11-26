#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterMultiGameMode.generated.h"

class AShooterMultiGameState;
UENUM(BlueprintType)
enum ETeam
{
	None = 00,
	Red,
	Blue
};

UCLASS()
class SHOOTERMULTI_API AShooterMultiGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	class AFlagActor* m_flag = nullptr;

protected:
	TObjectPtr<AShooterMultiGameState> m_gameState = nullptr;

public:
	AShooterMultiGameMode();

public:
	void MatchInit();
	void MatchBegin();
	void MatchEnd();

	TObjectPtr<AShooterMultiGameState> GetGameState() { return m_gameState; }
};

// GetSeamlessTraverActorList
// GetPlayersReady
// LoadSeamless