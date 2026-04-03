#include "StartPC.h"
#include "MyBlueprintFunctionLibrary.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

bool AStartPC::InputKey(const FInputKeyEventArgs& Params)
{
	if (Params.Event == EInputEvent::IE_Released && !Params.Key.IsMouseButton())
	{
		if (GetLocalPlayer())
		{
			int32 PlayerIndex = GetLocalPlayer()->GetLocalPlayerIndex();
			UMyBlueprintFunctionLibrary::SetActiveControllerID(GetWorld(), PlayerIndex);
		}

		//UMyBlueprintFunctionLibrary::RemoveAllPlayers(GetWorld());

		ensure(!NextLevel.IsNull());
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NextLevel);
	}

	return Super::InputKey(Params);
}