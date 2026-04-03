#include "GameHUD.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MyGameInstance.h"
#include "PauseWidget.h"
#include "MyBlueprintFunctionLibrary.h"
#include "PlayerStatWidget.h"
#include "GameFramework/Character.h"
#include "MyCustomCharacter.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());
	AMyPlayerController* PC = Cast<AMyPlayerController>(PlayerController);
	
	if (PC)
	{
		PlayerStatsWidget = CreateWidget<UPlayerStatWidget>(PC, PlayerStatsWidgetClass);
		if (PlayerStatsWidget)
		{
			PlayerStatsWidget->AddToViewport(0);
		}

		PC->GetOnNewPawnNotifier().AddUObject(this, &AGameHUD::OnPawnChanged);

		if (AMyCustomCharacter* Character = Cast<AMyCustomCharacter>(PC->GetCharacter()))
		{
			InitializePlayerStats(Character);
		}
	}

	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("GAME HUD BEGIN PLAY"));
	check(PlayerStatsWidget);
}

void AGameHUD::OnPawnChanged(APawn* NewPawn)
{
	if (AMyCustomCharacter* Character = Cast<AMyCustomCharacter>(NewPawn))
	{
		InitializePlayerStats(Character);
	}
}

void AGameHUD::InitializePlayerStats(AMyCustomCharacter* Character)
{
	if (!PlayerStatsWidget) return;

	UPlayerStats* PlayerStats = Character->FindComponentByClass<UPlayerStats>();
	if (PlayerStats)
	{
		PlayerStatsWidget->InitializeWithStats(PlayerStats);
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, TEXT("Player Stats Initialized Successfully."));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("Player Stats Failed To Initialize."));
	}
}

void AGameHUD::ShowPauseMenu()
{
	if (PauseMenuWidgetClass && !PauseMenuWidget)
	{
		APlayerController* OwningPlayer = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());
		PauseMenuWidget = CreateWidget<UUserWidget>(OwningPlayer, PauseMenuWidgetClass);

		if (PauseMenuWidget)
		{
			PauseMenuWidget->AddToViewport(100);
			PlayerStatsWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AGameHUD::HidePauseMenu()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->RemoveFromParent();
		PauseMenuWidget = nullptr;
		PlayerStatsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}