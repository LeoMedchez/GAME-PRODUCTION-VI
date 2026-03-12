#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "PlayerStats.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealthValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewStaminaValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENHANCEDTPTEMPLATEB_API UPlayerStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float currentHealth = maxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float maxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float currentStamina = maxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float maxStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	bool bStaminaDepleted = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool DecreaseHealth(float IncomingDamage);

	UFUNCTION(BlueprintCallable)
	void IncreaseHealth(float IncreaseByAmount);

	UFUNCTION(BlueprintCallable)
	bool DecreaseStamina(float DecreaseByAmount);

	UFUNCTION(BlueprintCallable)
	void IncreaseStamina(float IncreaseByAmount);

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChanged OnStaminaChanged;

	float GetHealthAsPercent() const;
	
	float GetStaminaAsPercent() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundCue* LowHealthSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundCue* LowStaminaSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundCue* HurtSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundCue* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	float LowHealthTreshold = 0.25;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	float LowStaminaTreshold = 0.5f;

	void HandleBreathAudio();

private:

	UPROPERTY()
	UAudioComponent* BreathAudioComp;

	UPROPERTY()
	UAudioComponent* HurtAudioComp;

	UFUNCTION()
	void OnBreathAudioFinished();

	bool bIsPlayingLowHealth = false;
	bool bIsPlayingLowStamina = false;
};
