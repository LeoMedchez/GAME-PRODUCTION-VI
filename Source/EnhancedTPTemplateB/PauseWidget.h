#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	const TSoftObjectPtr<UWorld> MainMenuLevel;

private:

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* BackgroundButton;

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnMainMenuButtonClicked();

	UFUNCTION()
	void OnQuitGameButtonClicked();
};
