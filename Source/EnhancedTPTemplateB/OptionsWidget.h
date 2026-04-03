#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsWidget.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* MuteMusicButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* EnableMusicButton;

	UFUNCTION()
	void OnMuteMusicButtonClicked();

	UFUNCTION()
	void OnEnableMusicButtonClicked();	
};
