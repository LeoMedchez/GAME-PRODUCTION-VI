#include "LoadingScreenModule.h"
#include "SLoadingScreenSlateWidget.h"
#include "MoviePlayer.h"
#include "LevelLoadingSettings.h"

void FLoadingScreenModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("FLoadingScreenModule::StartupModule"));

	if (ULevelLoadingSettings* Settings = GetMutableDefault<ULevelLoadingSettings>())
	{
		for(const FSoftObjectPath& BGPath : Settings->BackgroundImages)
		{
			if (!BGPath.IsNull())
			{
				UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(
					UTexture2D::StaticClass(), nullptr, *BGPath.ToString()));
				if (Texture)
				{
					LoadedBackgroundTextures.Add(Texture);
				}
			}
		}
	}
}

bool FLoadingScreenModule::IsGameModule() const
{
	return true;
}

void FLoadingScreenModule::StartLoadingScreen(const FString& MapName)
{
	UE_LOG(LogTemp, Warning, TEXT("FLoadingScreenModule::StarLoadingScreen"));

	ULevelLoadingSettings* Settings = GetMutableDefault<ULevelLoadingSettings>();

	bool bShouldShowLoadingScreen = false;

	for (const FSoftObjectPath& MapPath : Settings->MapsWithLoadingScreens)
	{
		if (MapPath.GetAssetPathString().Contains(MapName))
		{
			bShouldShowLoadingScreen = true;
			break;
		}
	}

	if (!bShouldShowLoadingScreen)
	{
		return;
	}

	FLoadingScreenAttributes LoadingScreen;

	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;

	LoadingScreen.MinimumLoadingScreenDisplayTime = Settings->MinimumLoadingScreenDisplayTime;

	LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreenSlateWidget).BackgroundTextures(LoadedBackgroundTextures).ImageSwitchInterval(Settings->ImageSwitchInterval);

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

IMPLEMENT_GAME_MODULE(FLoadingScreenModule, LoadingScreenModule);