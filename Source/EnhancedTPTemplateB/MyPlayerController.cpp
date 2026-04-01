#include "MyPlayerController.h"
#include "PlayerStatWidget.h"
#include "PlayerStats.h"
#include "GameFramework/Character.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	StatWidget = CreateWidget<UPlayerStatWidget>(this, WidgetClass);

	if (StatWidget)
	{
		StatWidget->AddToViewport();

		ACharacter* PlayerCharacter = GetCharacter();

		if (PlayerCharacter)
		{
			UPlayerStats* PlayerStats = PlayerCharacter->FindComponentByClass<UPlayerStats>();

			StatWidget->InitializeWithStats(PlayerStats);
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContext)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}

}