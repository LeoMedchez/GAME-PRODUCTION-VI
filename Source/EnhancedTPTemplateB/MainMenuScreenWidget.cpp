#include "MainMenuScreenWidget.h"
#include "CustomButton.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"

void UMainMenuScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton)
	{
		StartGameButton->GetButton()->SetFocus();
		StartGameButton->SetPlayFirstFocusSound(false);
		StartGameButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenWidget::OnStartGameButtonClicked);
	}

	if (ControlsButton)
	{
		ControlsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenWidget::OnControlsButtonClicked);
	}

	if (OptionsButton)
	{
		OptionsButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenWidget::OnOptionsButtonClicked);
	}

	if (QuitGameButton)
	{
		QuitGameButton->GetButton()->OnClicked.AddDynamic(this, &UMainMenuScreenWidget::OnQuitGameButtonClicked);
	}

	SetIsFocusable(true);

	PlayAnimation(MovingImage, 0, 0, EUMGSequencePlayMode::PingPong, 1.5);

	
	APlayerController* OwningPlayer = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(OwningPlayer->InputComponent))
	{
		//Using Macros to bind the correct Back Input Action
#if PLATFORM_SWITCH
		EnhancedInputComponent->BindAction(BackActionBottom, ETriggerEvent::Completed, this, &UMainMenuScreenWidget::Back);
#else
		EnhancedInputComponent->BindAction(BackActionRight, ETriggerEvent::Completed, this, &UMainMenuScreenWidget::Back);
#endif

	}
}

void UMainMenuScreenWidget::OnStartGameButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Start Game Button Clicked."));

	if (!NextLevel.IsNull())
	{
		SetFocus();
		UMyBlueprintFunctionLibrary::RemoveAllPlayers(GetWorld());
		UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay(this, NextLevel);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NextLevel is not set in UMainMenuScreenWidget."));
	}
}

void UMainMenuScreenWidget::OnQuitGameButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Quit Game Button Clicked."));
	SetFocus();
	UMyBlueprintFunctionLibrary::QuitAfterDelay(this);
}

void UMainMenuScreenWidget::OnControlsButtonClicked()
{
	ShowControlsWidget();
}

void UMainMenuScreenWidget::ShowControlsWidget()
{
	UIDataAsset = UMyBlueprintFunctionLibrary::GetUIDataAsset(GetWorld());

	if (!ControlsWidget)
	{
		APlayerController* OwningPlayer = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());
		ControlsWidget = CreateWidget<UUserWidget>(OwningPlayer, UIDataAsset->GetControlsWidget());

		if (ControlsWidget)
		{
			SetFocus();
			ControlsWidget->AddToViewport(100);
		}
	}
}

void UMainMenuScreenWidget::HideControlsWidget()
{
	if (ControlsWidget)
	{
		ControlsWidget->RemoveFromParent();
		ControlsWidget = nullptr;
	}
}

void UMainMenuScreenWidget::OnOptionsButtonClicked()
{
	ShowOptionsWidget();
}

void UMainMenuScreenWidget::ShowOptionsWidget()
{
	if (!OptionsWidget)
	{
		APlayerController* OwningPlayer = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());
		OptionsWidget = CreateWidget<UUserWidget>(OwningPlayer, OptionsWidgetClass);

		if (OptionsWidget)
		{
			SetFocus();
			OptionsWidget->AddToViewport(100);
		}
	}
}

void UMainMenuScreenWidget::HideOptionsWidget()
{
	if (OptionsWidget)
	{
		OptionsWidget->RemoveFromParent();
		OptionsWidget = nullptr;
	}
}


void UMainMenuScreenWidget::Back()
{
	UE_LOG(LogTemp, Warning, TEXT("Back Button Pressed"));

	if (GetWorld())
	{
		if (APlayerController* PC = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld()))
		{
			HideControlsWidget();
			HideOptionsWidget();

			StartGameButton->SetIsFocusable(true);
			StartGameButton->GetButton()->SetFocus();
		}
	}
}