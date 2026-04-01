#include "StartGM.h"
#include "StartPC.h"
#include "StartHUD.h"
#include "MyBlueprintFunctionLibrary.h"
#include "MyGameInstance.h"

AStartGM::AStartGM()
	:Super()
{
	PlayerControllerClass = AStartPC::StaticClass();

	HUDClass = AStartHUD::StaticClass();
}

void AStartGM::StartPlay()
{
	Super::StartPlay();

	UWorld* CurrentWorld = GetWorld();
	UGameInstance* GameInstance = CurrentWorld->GetGameInstance();

	for (int32 PlayerID = 0; PlayerID <= UMyBlueprintFunctionLibrary::GetLastMaxPlayerIndex(); ++PlayerID)
	{
		FString Error;
		ULocalPlayer* LocalPLayer = GameInstance->CreateLocalPlayer(PlayerID, Error, true);

		if (LocalPLayer)
		{
			UE_LOG(LogTemp, Log, TEXT("AStartGM::StartPlay: Created LocalPlayer with ID %d"), PlayerID);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("AStartGM::StartPlay: Failed to create LocalPlayer with ID: %d. Error: %s"), PlayerID, *Error);
		}
	}


	if (UMyGameInstance* GIRef = Cast<UMyGameInstance>(GameInstance))
	{
		GIRef->PlayStartScreenMusic();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("GameInstance Not Set."));
	}
}
