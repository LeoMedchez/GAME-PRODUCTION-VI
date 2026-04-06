#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AutoSaveGame.h"
#include "Blueprint/UserWidget.h"
#include "MyGameInstance.h"
#include "AutoSaveSubsystem.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UAutoSaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "AutoSave")
	void SetIsMuted(bool muted);

	UFUNCTION(BlueprintCallable, Category = "AutoSave")
	bool GetIsMuted();

	UFUNCTION()
	EActiveInputDevice GetSavedInputDevice() const;

	UFUNCTION()
	void SetSavedInputDevice(EActiveInputDevice NewDevice);

	UFUNCTION(BlueprintCallable, Category = "AutoSave")
	bool SaveGame();

	UFUNCTION(BlueprintCallable, Category = "AutoSave")
	void LoadGame();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SaveNotificationWidgetClass;

protected:

	UPROPERTY()
	UUserWidget* ActiveSaveNotificationWidget;

	bool bIsMuted;

	UPROPERTY()
	EActiveInputDevice SavedInputDevice = EActiveInputDevice::KeyboardMouse;

	void ShowSaveNotificationWidget();
	void HideSaveNotificationWidget();

private:

	FString SlotName = TEXT("AutoSaveSlot");
	FTimerHandle HideWidgetTimerHandle;
};
