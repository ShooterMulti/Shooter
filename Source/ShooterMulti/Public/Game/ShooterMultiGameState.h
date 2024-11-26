#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ShooterMultiGameState.generated.h"


class AShooterMultiPlayerState;

UCLASS()
class SHOOTERMULTI_API AShooterMultiGameState : public AGameStateBase
{
	GENERATED_BODY()
	friend class AFlagActor;

protected:
	TArray<AShooterMultiPlayerState*> m_playerStates;
	int m_flagLife;
	TArray<int> m_teamScores;

public:
	AShooterMultiGameState();

private:
	void ResetTeamScores();
	void ResetFlagLife();

public:
	void ResetValues();
	
	TObjectPtr<AShooterMultiPlayerState> GetPlayerState(const int _playerId) { return m_playerStates[_playerId]; }
	int GetFlagLife() { return m_flagLife; }
	int GetTeamScore(const int _teamId);
};
