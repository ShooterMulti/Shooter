#include "UI/StartMenuWidget.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"


void UStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// UI bindings
	// if (mm)
	// {
		// mm->OnTextChanged.AddDynamic(this, &UStartMenuWidget::OnUsernameTextBoxValidated);
	// }
	// if (bb)
	// {
		// bb->OnTextChanged.AddDynamic(this, &UStartMenuWidget::OnServerIpTextBoxValidated);
	// }
	if (m_hostButton)
	{
		m_hostButton->OnClicked.AddDynamic(this, &UStartMenuWidget::UStartMenuWidget::OnHostButtonClicked);
	}
	if (m_joinButton)
	{
		m_joinButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnJoinButtonClicked);
	}
	if (m_quitButton)
	{
		m_quitButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnQuitButtonClicked);
	}
}

// void UStartMenuWidget::OnUsernameTextBoxValidated(const FText& _text)
// {
// }

// void UStartMenuWidget::OnServerIpTextBoxValidated(const FText& _text)
// {
// }
	
void UStartMenuWidget::OnHostButtonClicked()
{
}

void UStartMenuWidget::OnJoinButtonClicked()
{
}

void UStartMenuWidget::OnQuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
