#include "MenuPC.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "MyGameInstance.h"

void AMenuPC::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// add the input mapping context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}

bool AMenuPC::InputKey(const FInputKeyEventArgs& Params)
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
