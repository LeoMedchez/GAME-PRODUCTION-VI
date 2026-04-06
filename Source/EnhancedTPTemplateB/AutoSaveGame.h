#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MyGameInstance.h"
#include "AutoSaveGame.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UAutoSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	bool bIsMuted;

	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	EActiveInputDevice InputDevice;

	UAutoSaveGame()
		:bIsMuted(false), InputDevice(EActiveInputDevice::KeyboardMouse)
	{
	}
};
