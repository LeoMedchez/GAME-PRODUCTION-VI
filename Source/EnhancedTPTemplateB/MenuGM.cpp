#include "MenuGM.h"
#include "MenuPC.h"
#include "MenuHUD.h"
#include "MyGameInstance.h"

AMenuGM::AMenuGM()
	:Super()
{
	PlayerControllerClass = AMenuPC::StaticClass();

	HUDClass = AMenuHUD::StaticClass();
}

void AMenuGM::StartPlay()
{
	Super::StartPlay();

	if (UMyGameInstance* gameInstanceRef = Cast<UMyGameInstance>(GetGameInstance()))
	{
		gameInstanceRef->PlayMenuMusic();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("GameInstance Not Set."));
	}
}
