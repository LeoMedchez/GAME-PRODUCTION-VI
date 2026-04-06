#include "MyPlayerController.h"
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

bool AMyPlayerController::InputKey(const FInputKeyEventArgs& Params)
{
	if (Params.Event == EInputEvent::IE_Pressed && !Params.Key.IsGamepadKey())
	{
		if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
		{
			if (GI->GetCurrentInputDevice() != EActiveInputDevice::KeyboardMouse)
			{
				GI->LastControllerDevice = GI->GetCurrentInputDevice();
				GI->SetCurrentInputDevice(EActiveInputDevice::KeyboardMouse);
			}
		}
	}

	return Super::InputKey(Params);
}