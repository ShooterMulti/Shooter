#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterMultiPlayerController.generated.h"

class APlayerCharacter;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

UCLASS()
class SHOOTERMULTI_API AShooterMultiPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;

	TObjectPtr<APlayerCharacter> PlayerCharacter;

	virtual void SetupInputComponent() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float walkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float dashSpeed = 1000.0f;

	bool bPlayerIsDashing = false;

	UFUNCTION(BlueprintCallable)
	APlayerCharacter* GetPlayerCharacter() const { return PlayerCharacter; }

private:
	// Input Mapping Context
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> defaultMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> moveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> lookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> jumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> fireAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> reloadAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> dashAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> switchInputModeAction;

public:
	// Actions Input Functions
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Jump(const FInputActionValue& value);
	void Fire(const FInputActionValue& value);
	void Reload(const FInputActionValue& value); // TODO
	void Dash(const FInputActionValue& value);  // TODO

	void SwitchInputMode(const FInputActionValue& value);
};