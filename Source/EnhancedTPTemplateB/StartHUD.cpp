#include "StartHUD.h"
#include "Blueprint/UserWidget.h"

void AStartHUD::BeginPlay()
{
	Super::BeginPlay();

	ensure(StartScreenClass != nullptr);

	if (StartScreenClass != nullptr)
	{
		UUserWidget* StartScreen = CreateWidget<UUserWidget>(GetWorld(), StartScreenClass);
		StartScreen->AddToViewport();
	}
}