#include "Team/TeamManager.h"


TeamManager::TeamManager()
{
}

TeamManager::~TeamManager()
{
}

Team* TeamManager::GetSmallestTeam()
{
	Team* smallestTeam = nullptr;

	// Loop through all teams and get the one with the least amount of player
	for (int i = 0; i < m_teams.Num(); i++)
	{
		if (smallestTeam == nullptr || m_teams[i]->GetPlayerCount() < smallestTeam->GetPlayerCount())
		{
			smallestTeam = m_teams[i];
		}
	}
	
	return smallestTeam;
}

void TeamManager::CreateTeam()
{
	Team* newTeam = new Team(m_teams.Num());
	m_teams[m_teams.Num()] = newTeam;
}

void TeamManager::AssignTeam(AShooterMultiPlayerState* _playerState)
{
	GetSmallestTeam()->AddPlayer(_playerState);
}
