#include "AutoSaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void UAutoSaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadGame();
}

void UAutoSaveSubsystem::Deinitialize()
{
	GetWorld()->GetTimerManager().ClearTimer(HideWidgetTimerHandle);
	Super::Deinitialize();
}

void UAutoSaveSubsystem::SetIsMuted(bool muted)
{
	bIsMuted = muted;
	ShowSaveNotificationWidget();
}

bool UAutoSaveSubsystem::GetIsMuted()
{
	return bIsMuted;
}

EActiveInputDevice UAutoSaveSubsystem::GetSavedInputDevice() const
{
	return SavedInputDevice;
}

void UAutoSaveSubsystem::SetSavedInputDevice(EActiveInputDevice NewDevice)
{
	SavedInputDevice = NewDevice;
	ShowSaveNotificationWidget();
}

bool UAutoSaveSubsystem::SaveGame()
{
	UAutoSaveGame* SaveGameInstance = Cast<UAutoSaveGame>(UGameplayStatics::CreateSaveGameObject(UAutoSaveGame::StaticClass()));
	if (!SaveGameInstance) return false;

	SaveGameInstance->bIsMuted;
	SaveGameInstance->InputDevice;

	return UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}

void UAutoSaveSubsystem::LoadGame()
{
	if (UAutoSaveGame* LoadedGame = Cast<UAutoSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
	{
		bIsMuted = LoadedGame->bIsMuted;
		SavedInputDevice = LoadedGame->InputDevice;
	}
	else
	{
		bIsMuted = false;
		SavedInputDevice = EActiveInputDevice::KeyboardMouse;
	}
}

void UAutoSaveSubsystem::ShowSaveNotificationWidget()
{
	if (SaveNotificationWidgetClass && !ActiveSaveNotificationWidget)
	{
		ActiveSaveNotificationWidget = CreateWidget<UUserWidget>(GetWorld(), SaveNotificationWidgetClass);
		if (ActiveSaveNotificationWidget)
		{
			ActiveSaveNotificationWidget->AddToViewport();
			GetWorld()->GetTimerManager().SetTimer(HideWidgetTimerHandle, this, &UAutoSaveSubsystem::HideSaveNotificationWidget, 2.0f, false);
		}
	}
}

void UAutoSaveSubsystem::HideSaveNotificationWidget()
{
	if (ActiveSaveNotificationWidget)
	{
		ActiveSaveNotificationWidget->RemoveFromParent();
		ActiveSaveNotificationWidget = nullptr;
	}
}