#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LevelLoadingSettings.generated.h"

UCLASS(Config = "Game", DefaultConfig, meta = (DisplayName = "Loading Screen"))
class LOADINGSCREENMODULE_API ULevelLoadingSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen", meta = (AllowedClasses = "World"))
	TArray<FSoftObjectPath> MapsWithLoadingScreens;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen", meta = (AllowedClasses = "Texture"))
	FSoftObjectPath BackgroundImage;

	UPROPERTY(Config, EditAnywhere, Category = "Loading Screen")
	float MinimumLoadingScreenDisplayTime = 2.0f;

};
