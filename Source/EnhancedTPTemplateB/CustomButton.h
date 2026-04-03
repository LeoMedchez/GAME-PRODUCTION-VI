#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateTypes.h"
#include "CustomButton.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UCustomButton : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UFUNCTION(BlueprintCallable)
	UButton* GetButton() const { return Button; }

	UFUNCTION(BlueprintCallable)
	void SetIsFocused(bool bValue) { bIsFocused = bValue; }

private:

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ButtonText;

private:

	UPROPERTY(EditAnywhere, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	FText ButtonTextValue;

	UPROPERTY(EditDefaultsOnly, Category = "Button Style", meta = (AllowPrivateAccess = "true"))
	FButtonStyle FocusedStyle;

	FButtonStyle DefaultStyle;

	bool bIsFocused;

private:

	UPROPERTY(EditAnywhere, Category = "Defaults", meta = (AllowPrivateAccess = "true"))
	bool bPlayFirstFocusSound = true;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
	class USoundBase* FocusSound;

	void PlaySound();

public:

	void SetPlayFirstFocusSound(bool bValue) { bPlayFirstFocusSound = bValue; }
};
