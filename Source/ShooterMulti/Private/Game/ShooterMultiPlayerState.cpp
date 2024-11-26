#include "Game/ShooterMultiPlayerState.h"

#include "Net/UnrealNetwork.h"


void AShooterMultiPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShooterMultiPlayerState, username);
	DOREPLIFETIME(AShooterMultiPlayerState, life);
	DOREPLIFETIME(AShooterMultiPlayerState, team);
}

void AShooterMultiPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	AShooterMultiPlayerState* newPlayerState = Cast<AShooterMultiPlayerState>(PlayerState);

	if (newPlayerState)
	{
		newPlayerState->team = team;
		newPlayerState->life = life;
		newPlayerState->username = username;
	}
}
