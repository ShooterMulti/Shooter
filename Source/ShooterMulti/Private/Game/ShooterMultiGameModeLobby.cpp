#include "Game/ShooterMultiGameModeLobby.h"


AShooterMultiGameModeLobby::AShooterMultiGameModeLobby()
{
}

void AShooterMultiGameModeLobby::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
}
