#include "Team/Team.h"


Team::Team(int _id)
	: m_id(_id), m_score(0)
{}

Team::~Team()
{
}

void Team::IncrementScore()
{
	m_score++;
}

void Team::AddPlayer(AShooterMultiPlayerState* _playerState)
{
	m_players[m_players.Num()] = _playerState;
}
