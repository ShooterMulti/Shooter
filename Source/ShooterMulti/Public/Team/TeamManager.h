#pragma once

#include "CoreMinimal.h"
#include "Team.h"
#include "Game/ShooterMultiPlayerState.h"


class SHOOTERMULTI_API TeamManager
{
private:
	TMap<int, Team*> m_teams;

public:
	TeamManager();
	~TeamManager();

private:
	// Get the team with the least amount of players
	Team* GetSmallestTeam();
	
public:
	// Create a new team and add it to m_teams TMap
	void CreateTeam();
	void AssignTeam(AShooterMultiPlayerState* _playerState);
};
