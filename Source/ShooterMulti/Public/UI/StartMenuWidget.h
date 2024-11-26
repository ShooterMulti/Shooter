#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"


UCLASS()
class SHOOTERMULTI_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Username text box
	// UPROPERTY(meta = (BindWidget))
	// class UEditableTextBox* mm = nullptr;
	// Ip text box
	// UPROPERTY(meta = (BindWidget))
	// class UEditableTextBox* bb;

	UPROPERTY(meta = (BindWidget))
	class UButton* m_hostButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* m_joinButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	class UButton* m_quitButton = nullptr;
	
protected:
	virtual void NativeConstruct() override;

	// UFUNCTION()
	// void OnUsernameTextBoxValidated(const FText& _text);
	// UFUNCTION()
	// void OnServerIpTextBoxValidated(const FText& _text);
	
	UFUNCTION()
	void OnHostButtonClicked();
	UFUNCTION()
	void OnJoinButtonClicked();
	UFUNCTION()
	void OnQuitButtonClicked();
};
