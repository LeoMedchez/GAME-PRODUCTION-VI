#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatWidget.generated.h"

class UProgressBar;
class UPlayerStats;

UCLASS()
class ENHANCEDTPTEMPLATEB_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

public:

	void InitializeWithStats(UPlayerStats* StatComp);

private:

	UFUNCTION()
	void OnHealthChanged(float healthValue);

	UFUNCTION()
	void OnStaminaChanged(float staminaValue);

	UPlayerStats* PlayerStats;
};
