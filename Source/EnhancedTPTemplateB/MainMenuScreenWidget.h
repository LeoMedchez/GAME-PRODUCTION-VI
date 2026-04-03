#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "UIDataAsset.h"
#include "MainMenuScreenWidget.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UMainMenuScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly)
	const TSoftObjectPtr<UWorld> NextLevel;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> MovingImage;

private:
	UPROPERTY(meta = (BindWidget))
	class UCustomButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* BackgroundButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* ControlsButton;

	UPROPERTY(meta = (BindWidget))
	class UCustomButton* OptionsButton;
	
	UPROPERTY()
	UUIDataAsset* UIDataAsset;

	UPROPERTY()
	class UUserWidget* ControlsWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> OptionsWidgetClass;

	UPROPERTY()
	class UUserWidget* OptionsWidget;

	UFUNCTION()
	void OnStartGameButtonClicked();

	UFUNCTION()
	void OnQuitGameButtonClicked();

	UFUNCTION()
	void OnControlsButtonClicked();

	UFUNCTION()
	void OnOptionsButtonClicked();

public:

	void ShowControlsWidget();
	void HideControlsWidget();
	void Back();

	void ShowOptionsWidget();
	void HideOptionsWidget();

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BackActionRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* BackActionBottom;
};
