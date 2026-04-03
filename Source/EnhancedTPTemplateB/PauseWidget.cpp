#include "PauseWidget.h"
#include "MyBlueprintFunctionLibrary.h"
#include "CustomButton.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "MyCustomCharacter.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->GetButton()->SetFocus();
		ResumeButton->SetPlayFirstFocusSound(false);
		ResumeButton->GetButton()->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeButtonClicked);
	}

	if (MainMenuButton)
	{
		MainMenuButton->GetButton()->OnClicked.AddDynamic(this, &UPauseWidget::OnMainMenuButtonClicked);
	}

	if (QuitGameButton)
	{
		QuitGameButton->GetButton()->OnClicked.AddDynamic(this, &UPauseWidget::OnQuitGameButtonClicked);
	}

	SetIsFocusable(true);
}

void UPauseWidget::OnResumeButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Resume Button Clicked"));

	if (ACharacter* MyCharacter = UMyBlueprintFunctionLibrary::GetActivePlayerCharacter(GetWorld()))
	{
		if (AMyCustomCharacter* PlayerCharacter = Cast<AMyCustomCharacter>(MyCharacter))
		{
			PlayerCharacter->DoPause();
		}
	}
}

void UPauseWidget::OnMainMenuButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Main Menu Button Clicked"));

	if (APlayerController* PC = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld()))
	{
		if (!MainMenuLevel.IsNull())
		{
			SetFocus();

			PC->SetPause(false);
			UMyBlueprintFunctionLibrary::RemoveAllPlayers(GetWorld());
			UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay(this, MainMenuLevel);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("MainMenuLevel is not set in PauseWidget"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No Active PlayerController Found To Return To Main Menu"));
	}

}

void UPauseWidget::OnQuitGameButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Quit Game Button Clicked"));

	APlayerController* PC = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());

	if (!PC) return;

	PC->SetPause(false);
	SetFocus();

	UMyBlueprintFunctionLibrary::QuitAfterDelay(this);
}