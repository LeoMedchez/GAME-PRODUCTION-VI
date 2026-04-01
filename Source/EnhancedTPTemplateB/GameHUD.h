#pragma once

#include "CoreMinimal.h"
#include "BaseHUD.h"
#include "GameHUD.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API AGameHUD : public ABaseHUD
{
	GENERATED_BODY()
	
public:
	AGameHUD();

protected:

	/** Initialization */
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pause Menu", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass;

	UPROPERTY()
	class UUserWidget* PauseMenuWidget;

public:

	void ShowPauseMenu();
	void HidePauseMenu();

};
