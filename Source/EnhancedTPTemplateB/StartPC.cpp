#include "StartPC.h"
#include "MyBlueprintFunctionLibrary.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

bool AStartPC::InputKey(const FInputKeyEventArgs& Params)
{
	if (Params.Event == EInputEvent::IE_Released && !Params.Key.IsMouseButton())
	{
		if (GetLocalPlayer())
		{
			int32 PlayerIndex = GetLocalPlayer()->GetLocalPlayerIndex();
			UMyBlueprintFunctionLibrary::SetActiveControllerID(GetWorld(), PlayerIndex);
		}

		if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
		{
			if (Params.Key.IsGamepadKey())
			{
				GI->SetCurrentInputDevice(EActiveInputDevice::Xbox);
			}
			else
			{
				GI->SetCurrentInputDevice(EActiveInputDevice::KeyboardMouse);
			}
		}

		UMyBlueprintFunctionLibrary::RemoveAllPlayers(GetWorld());

		ensure(!NextLevel.IsNull());
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NextLevel);
	}

	return Super::InputKey(Params);
}