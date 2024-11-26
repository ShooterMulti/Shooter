#include "Game/ShooterMultiGameState.h"


AShooterMultiGameState::AShooterMultiGameState()
{
	ResetValues();
}

void AShooterMultiGameState::ResetTeamScores()
{
	for (int i = 0; i < m_teamScores.Num(); i++)
	{
		m_teamScores[i] = 0;
	}
}

void AShooterMultiGameState::ResetFlagLife()
{
	// Reset flag life
}

void AShooterMultiGameState::ResetValues()
{
	ResetTeamScores();
	ResetFlagLife();
}

int AShooterMultiGameState::GetTeamScore(const int _teamId)
{
	switch (_teamId)
	{
	case 0:
		return m_teamScores[0];

	case 1:
		return m_teamScores[1];

	default:
		return -1;
	}
}
