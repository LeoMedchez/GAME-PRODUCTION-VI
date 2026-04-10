#include "GameGM.h"
#include "MyPlayerController.h"
#include "GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "CharacterSelectInterface.h"

AGameGM::AGameGM()
	: Super()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();

	HUDClass = AGameHUD::StaticClass();
}

void AGameGM::StartPlay()
{
	Super::StartPlay();
	UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstanceRef)
	{
		if (GameInstanceRef->GetActiveControllerID() > -1)
		{
			APlayerController* PC = UGameplayStatics::CreatePlayer(this, GameInstanceRef->GetActiveControllerID());

			FInputModeGameOnly InputMode;

			if (PC != nullptr)
				PC->SetInputMode(InputMode);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("ControllerID is not Set"));
		}

		GameInstanceRef->PlayGameplayMusic();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("GameInstance is not Set"));
	}
}

UClass* AGameGM::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		TSubclassOf<APawn> SelectedClass = ICharacterSelectInterface::Execute_GetSelectedCharacter(GI);

		if (SelectedClass)
		{
			return SelectedClass;
		}
	}

	return DefaulfCharacterClass ? (UClass*)DefaulfCharacterClass :
		Super::GetDefaultPawnClassForController_Implementation(InController);
}
