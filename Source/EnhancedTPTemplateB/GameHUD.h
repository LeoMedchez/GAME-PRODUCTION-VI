#pragma once

#include "CoreMinimal.h"
#include "BaseHUD.h"
#include "MyCustomCharacter.h"
#include "GameHUD.generated.h"

class UPlayerStats;
class UUserWidget;
class UPlayerStatWidget;

UCLASS()
class ENHANCEDTPTEMPLATEB_API AGameHUD : public ABaseHUD
{
	GENERATED_BODY()
	
public:
	AGameHUD();

protected:

	/** Initialization */
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UPlayerStatWidget> PlayerStatsWidgetClass;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY()
	UPlayerStatWidget* PlayerStatsWidget;

	UPROPERTY()
	UUserWidget* PauseMenuWidget;

	UFUNCTION()
	void OnPawnChanged(APawn* NewPawn);

	void InitializePlayerStats(AMyCustomCharacter* Character);

public:

	void ShowPauseMenu();
	void HidePauseMenu();
};
