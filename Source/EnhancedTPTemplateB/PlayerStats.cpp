#include "PlayerStats.h"

// Sets default values for this component's properties
UPlayerStats::UPlayerStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerStats::BeginPlay()
{
	Super::BeginPlay();

	BreathAudioComp = NewObject<UAudioComponent>(this);
	BreathAudioComp->RegisterComponent();
	BreathAudioComp->AttachToComponent(
		GetOwner()->GetRootComponent(),
		FAttachmentTransformRules::KeepRelativeTransform);

	HurtAudioComp = NewObject<UAudioComponent>(this);
	HurtAudioComp->RegisterComponent();
	HurtAudioComp->AttachToComponent(
		GetOwner()->GetRootComponent(),
		FAttachmentTransformRules::KeepRelativeTransform);

	BreathAudioComp->OnAudioFinished.AddDynamic(this, &UPlayerStats::OnBreathAudioFinished);
}


// Called every frame
void UPlayerStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	HandleBreathAudio();
}

bool UPlayerStats::DecreaseHealth(float IncomingDamage)
{
	currentHealth -= IncomingDamage;

	OnHealthChanged.Broadcast(GetHealthAsPercent());

	if (HurtAudioComp && HurtSound)
	{
		HurtAudioComp->SetSound(HurtSound);
		HurtAudioComp->Play();
	}

	bIsDead = currentHealth <= 0.0f;

	if (bIsDead)
	{
		if (BreathAudioComp && BreathAudioComp->IsPlaying())
		{
			BreathAudioComp->Stop();
		}

		if (HurtAudioComp && DeathSound)
		{
			HurtAudioComp->SetSound(DeathSound);
			HurtAudioComp->Play();
		}

		bIsPlayingLowHealth = false;
		bIsPlayingLowStamina = false;
	}

	return bIsDead;
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

void UPlayerStats::HandleBreathAudio()
{
	if (!BreathAudioComp) return;

	if (bIsDead)
	{
		if (BreathAudioComp->IsPlaying())
		{
			BreathAudioComp->Stop();
		}

		bIsPlayingLowHealth = false;
		bIsPlayingLowStamina = false;
		
		return;
	}

	bool bLowHealth = GetHealthAsPercent() <= LowHealthTreshold;
	bool bLowStamina = GetStaminaAsPercent() <= LowStaminaTreshold;

	if (bLowHealth)
	{
		if (!bIsPlayingLowHealth && LowHealthSound)
		{
			BreathAudioComp->SetSound(LowHealthSound);
			BreathAudioComp->Play();

			bIsPlayingLowHealth = true;
			bIsPlayingLowStamina = false;
		}
	}
	else if (bLowStamina)
	{
		if (!bIsPlayingLowStamina && LowStaminaSound)
		{
			BreathAudioComp->SetSound(LowStaminaSound);
			BreathAudioComp->Play();
			bIsPlayingLowStamina = true;
			bIsPlayingLowHealth = false;
		}
	}
	else
	{
		if (BreathAudioComp->IsPlaying())
		{
			BreathAudioComp->Stop();
		}
		
		bIsPlayingLowHealth = false;
		bIsPlayingLowStamina = false;
	}
}

void UPlayerStats::OnBreathAudioFinished()
{
	bool bLowHealth = GetHealthAsPercent() <= LowHealthTreshold;
	bool bLowStamina = GetStaminaAsPercent() <= LowStaminaTreshold;

	if (bLowHealth && LowHealthSound)
	{
		BreathAudioComp->Play();
	}
	else if (bLowStamina && LowStaminaSound)
	{
		BreathAudioComp->Play();
	}
	else
	{
		bIsPlayingLowHealth = false;
		bIsPlayingLowStamina = false;
	}
}
