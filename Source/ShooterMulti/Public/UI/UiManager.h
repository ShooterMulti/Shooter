#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UiManager.generated.h"

UCLASS()
class SHOOTERMULTI_API AUiManager : public AActor
{
	GENERATED_BODY()

protected:
#pragma region Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> m_startMenuWidgetClass = nullptr;
	TObjectPtr<UUserWidget> m_startMenuInstance = nullptr;
#pragma endregion Widgets
	
public:	
	AUiManager() = default;
};
