#include "GameHUD.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MyGameInstance.h"
//#include "PauseWidget.h"
#include "MyBlueprintFunctionLibrary.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
}

	//UNCOMMENT ONCE PAUSE WIDGET IS CREATED
//void AGameHUD::ShowPauseMenu()
//{
//	if (PauseMenuWidgetClass && !PauseMenuWidget)
//	{
//		APlayerController* OwningPlayer = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld());
//		PauseMenuWidget = CreateWidget<UUserWidget>(OwningPlayer, PauseMenuWidgetClass);
//
//		if (PauseMenuWidget)
//		{
//			PauseMenuWidget->AddToViewport(100);
//			UserInterface->SetVisibility(ESlateVisibility::Hidden);
//		}
//	}
//}
//
//void AGameHUD::HidePauseMenu()
//{
//	if (PauseMenuWidget)
//	{
//		PauseMenuWidget->RemoveFromParent();
//		PauseMenuWidget = nullptr;
//		UserInterface->SetVisibility(ESlateVisibility::Visible);
//	}
//}