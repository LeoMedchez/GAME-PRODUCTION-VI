#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ControllerDisconnectedWidget.h"
#include "MyGameInstance.generated.h"

UENUM(BlueprintType)
enum class EActiveInputDevice : uint8
{
	KeyboardMouse,
	PlayStation,
	Xbox,
	Switch
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputDeviceChanged, EActiveInputDevice, NewDevice);

UCLASS()
class ENHANCEDTPTEMPLATEB_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	FTSTicker::FDelegateHandle TickDelegateHandle;
	int32 CurrentActiveControllerID = -1;

private:

	bool bDidControllerDisconnectPauseGame = false;

	UPROPERTY()
	UControllerDisconnectedWidget* ControllerDisconnectedWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UControllerDisconnectedWidget> ControllerDisconnectedWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> SaveNotificationWidgetClass;

public:

	static const int32 MAX_CONTROLLERS = 4;

	virtual void Init() override;
	virtual void Shutdown() override;

	bool Tick(float DeltaSeconds);

	void SetActiveControllerID(int32 ControllerID);
	int32 GetActiveControllerID();

	UFUNCTION()
	virtual void BeginLoadingScreen(const FString& MapName);

	UFUNCTION()
	virtual void EndLoadingScreen(UWorld* InLoadedWorld);

private:
	
	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUIDataAsset* PCUIDataAsset;

	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUIDataAsset* XboxUIDataAsset;

	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUIDataAsset* PS5UIDataAsset;

	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UUIDataAsset* SwitchUIDataAsset;

	UFUNCTION()
	void OnInputDeviceChangedHandler(EActiveInputDevice NewDevice);

	EActiveInputDevice CurrentInputDevice = EActiveInputDevice::KeyboardMouse;

public:

	UPROPERTY(BlueprintAssignable, Category = "Input")
	FOnInputDeviceChanged OnInputDeviceChanged;

	UFUNCTION(BlueprintCallable, Category = "Input")
	EActiveInputDevice GetCurrentInputDevice() const { return CurrentInputDevice; }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetCurrentInputDevice(EActiveInputDevice NewDevice);

	UFUNCTION(BlueprintCallable)
	class UUIDataAsset* GetUIDataAsset() const;

	UFUNCTION(BlueprintCallable)
	class UUIDataAsset* GetUIDataAssetForCurrentDevice() const;

	UFUNCTION(BlueprintCallable)
	void OnControllerChanged(EInputDeviceConnectionState connectionState, FPlatformUserId userID, FInputDeviceId inputDeviceID);

	void DismissControllerDisconnectWidget();
	
	EActiveInputDevice LastControllerDevice = EActiveInputDevice::Xbox;

private:

	UPROPERTY()
	class UAudioComponent* GameplayMusicAudioComponent;

	UPROPERTY()
	class UAudioComponent* MenuMusicAudioComponent;

	UPROPERTY()
	class UAudioComponent* StartScreenMusicAudioComponent;

	UPROPERTY()
	class UAudioComponent* GameOverScreenMusicAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Music", meta = (AllowPrivateAccess = "true"))
	class USoundBase* GameplayMusic;

	UPROPERTY(EditAnywhere, Category = "Music", meta = (AllowPrivateAccess = "true"))
	class USoundBase* MenuMusic;

	UPROPERTY(EditAnywhere, Category = "Music", meta = (AllowPrivateAccess = "true"))
	class USoundBase* StartScreenMusic;

	UPROPERTY(EditAnywhere, Category = "Music", meta = (AllowPrivateAccess = "true"))
	class USoundBase* GameOverMusic;

	UPROPERTY(EditAnywhere, Category = "Music", meta = (AllowPrivateAccess = "true"))
	float MusicFadeDuration = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Music", meta = (AllowPrivateAccess = "true"))
	bool bisMusicMuted = false;

public:

	UFUNCTION(BlueprintCallable)
	void PlayGameplayMusic();

	UFUNCTION(BlueprintCallable)
	void StopGameplayMusic(bool ForceStop = false);

	UFUNCTION(BlueprintCallable)
	void PlayMenuMusic();

	UFUNCTION(BlueprintCallable)
	void StopMenuMusic(bool ForceStop = false);

	UFUNCTION(BlueprintCallable)
	void PlayStartScreenMusic();

	UFUNCTION(BlueprintCallable)
	void StopStartScreenMusic(bool ForceStop = false);

	UFUNCTION(BlueprintCallable)
	void PlayGameOverMusic();

	UFUNCTION(BlueprintCallable)
	void StopGameOverMusic(bool ForceStop = false);

	UFUNCTION()
	void StopAllMusic();

	UFUNCTION()
	void EnableAllMusic();
};
