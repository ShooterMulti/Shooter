#include "Player/ShooterMultiPlayerController.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

void AShooterMultiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

}

void AShooterMultiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(moveAction, ETriggerEvent::Triggered, this, &AShooterMultiPlayerController::Move);
		EnhancedInput->BindAction(lookAction, ETriggerEvent::Triggered, this, &AShooterMultiPlayerController::Look);
		EnhancedInput->BindAction(jumpAction, ETriggerEvent::Triggered, this, &AShooterMultiPlayerController::Jump);
		EnhancedInput->BindAction(fireAction, ETriggerEvent::Started, this, &AShooterMultiPlayerController::Fire);
		EnhancedInput->BindAction(reloadAction, ETriggerEvent::Started, this, &AShooterMultiPlayerController::Reload);

		EnhancedInput->BindAction(dashAction, ETriggerEvent::Triggered, this, &AShooterMultiPlayerController::Dash);
		EnhancedInput->BindAction(dashAction, ETriggerEvent::Completed, this, &AShooterMultiPlayerController::Dash);

		EnhancedInput->BindAction(switchInputModeAction, ETriggerEvent::Triggered, this, &AShooterMultiPlayerController::SwitchInputMode);
	}
}

void AShooterMultiPlayerController::Move(const FInputActionValue& value)
{
	if (PlayerCharacter && value.Get<bool>())
	{
		PlayerCharacter->Move(value);
	}
}

void AShooterMultiPlayerController::Look(const FInputActionValue& value)
{
	if (PlayerCharacter && value.Get<bool>())
	{
		PlayerCharacter->Look(value);
	}
}

void AShooterMultiPlayerController::Jump(const FInputActionValue& value)
{
	if (PlayerCharacter && value.Get<bool>())
	{
		PlayerCharacter->Jump();
	}
}

void AShooterMultiPlayerController::Fire(const FInputActionValue& value)
{
	if (PlayerCharacter && value.Get<bool>())
	{
		PlayerCharacter->Fire();
	}
}

void AShooterMultiPlayerController::Reload(const FInputActionValue& value)
{
	if (PlayerCharacter && value.Get<bool>())
	{
		PlayerCharacter->Reload();
	}
}

void AShooterMultiPlayerController::Dash(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		if (PlayerCharacter)
		{
			PlayerCharacter->Dash(dashSpeed);
		}
	}
	else
	{
		if(PlayerCharacter)
		{
			PlayerCharacter->Dash(walkSpeed);
		}
	}
}

void AShooterMultiPlayerController::SwitchInputMode(const FInputActionValue& value)
{
	if(value.Get<bool>())
	{
		DisableInput(GetWorld()->GetFirstPlayerController());
		SetShowMouseCursor(true);
	}
}