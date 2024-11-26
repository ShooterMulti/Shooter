#include "Game/ShooterMultiGameMode.h"
#include "Game/ShooterMultiGameState.h"

#include "Game/ShooterMultiSceneObjectGetter.h"
#include "Flag/FlagActor.h"

AShooterMultiGameMode::AShooterMultiGameMode()
{
	
}

void AShooterMultiGameMode::MatchInit()
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Purple, FString::Printf(TEXT("Match Init"))); // TODELETE
	// Reset GameState
	//m_gameState->Reset();//TODO Get the game state correctly
	// Spawn players to their given (random) start positions

	AShooterMultiSceneObjectGetter::GetInstance()->flag->ChooseSpawnLocation();
	AShooterMultiSceneObjectGetter::GetInstance()->flag->Spawn();

	// Spawn Flag
}

void AShooterMultiGameMode::MatchBegin()
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Purple, FString::Printf(TEXT("Match Begin"))); // TODELETE
}

void AShooterMultiGameMode::MatchEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Purple, FString::Printf(TEXT("Match End"))); // TODELETE
}
