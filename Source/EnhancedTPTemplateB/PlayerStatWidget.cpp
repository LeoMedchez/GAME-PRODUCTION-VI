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
	HealthBar->SetPercent(healthValue);
}

void UPlayerStatWidget::OnStaminaChanged(float staminaValue)
{
	StaminaBar->SetPercent(staminaValue);
}
