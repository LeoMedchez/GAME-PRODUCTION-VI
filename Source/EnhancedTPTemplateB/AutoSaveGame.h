#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "AutoSaveGame.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UAutoSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, Category = "Save Data")
	bool bIsMuted;

	UAutoSaveGame()
		:bIsMuted(false)
	{
	}
};
