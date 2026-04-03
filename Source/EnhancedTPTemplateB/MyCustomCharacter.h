#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCustomCharacter.generated.h"

class UInputAction;

UCLASS()
class ENHANCEDTPTEMPLATEB_API AMyCustomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCustomCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BackActionRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* BackActionBottom;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	/** Handles Pause Input From Either Controls or UI Interfaces */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoPause();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Back();

private:

	bool IsPaused() const;
	void Pause();
	void UnPause();
};
