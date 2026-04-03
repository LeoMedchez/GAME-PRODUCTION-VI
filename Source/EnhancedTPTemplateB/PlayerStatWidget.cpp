#include "PlayerStatWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerStats.h"

void UPlayerStatWidget::InitializeWithStats(UPlayerStats* StatComp)
{
	PlayerStats = StatComp;

	if (!PlayerStats) return;

	PlayerStats->OnHealthChanged.AddDynamic(this, &UPlayerStatWidget::OnHealthChanged);
	PlayerStats->OnStaminaChanged.AddDynamic(this, &UPlayerStatWidget::OnStaminaChanged);

	HealthBar->SetPercent(PlayerStats->GetHealthAsPercent());
	StaminaBar->SetPercent(PlayerStats->GetStaminaAsPercent());
}

void UPlayerStatWidget::OnHealthChanged(float healthValue)
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("Health UI Updated"));
	HealthBar->SetPercent(healthValue);
}

void UPlayerStatWidget::OnStaminaChanged(float staminaValue)
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("Stamina UI Updated"));
	StaminaBar->SetPercent(staminaValue);
}
