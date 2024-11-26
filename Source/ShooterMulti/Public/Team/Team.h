#pragma once

#include "CoreMinimal.h"
#include "Game/ShooterMultiPlayerState.h"


class SHOOTERMULTI_API Team
{
private:
	int m_id;
	int m_score;
	TArray<APlayerState*> m_players;
	
public:
	Team(int _id);
	~Team();

public:
	// Used when player destroys flag
	void IncrementScore();
	// Add a player to the team
	void AddPlayer(AShooterMultiPlayerState* _playerState);

	int GetScore() { return m_score; }
	int GetPlayerCount() { return m_players.Num(); }
};
