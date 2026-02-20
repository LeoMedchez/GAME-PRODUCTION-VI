#include "PlayerStats.h"

// Sets default values for this component's properties
UPlayerStats::UPlayerStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPlayerStats::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPlayerStats::DecreaseHealth(float IncomingDamage)
{
	currentHealth -= IncomingDamage;

	OnHealthChanged.Broadcast(GetHealthAsPercent());

	return bIsDead = currentHealth <= 0.0f;
}

void UPlayerStats::IncreaseHealth(float IncreaseByAmount)
{
	currentHealth += IncreaseByAmount;

	if (currentHealth > maxHealth)
	{
		currentHealth = maxHealth;
	}

	OnHealthChanged.Broadcast(GetHealthAsPercent());
}

bool UPlayerStats::DecreaseStamina(float DecreaseByAmount)
{
	currentStamina -= DecreaseByAmount;

	OnStaminaChanged.Broadcast(GetStaminaAsPercent());

	return bStaminaDepleted = currentStamina <= 0.0f;
}

void UPlayerStats::IncreaseStamina(float IncreaseByAmount)
{
	currentStamina += IncreaseByAmount;

	if (currentStamina > maxStamina)
	{
		currentStamina = maxStamina;
	}

	OnStaminaChanged.Broadcast(GetStaminaAsPercent());
}

float UPlayerStats::GetHealthAsPercent() const
{
	return currentHealth / maxHealth;
}

float UPlayerStats::GetStaminaAsPercent() const
{
	return currentStamina / maxStamina;
}

