#include "MyGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "GenericPlatform/GenericPlatformInputDeviceMapper.h"
#include "Kismet/KismetStringLibrary.h"
#include "MyBlueprintFunctionLibrary.h"
#include "LoadingScreenModule.h"
#include "CustomGameViewportClient.h"
#include "Components/AudioComponent.h"
//#include "AutoSaveSubsystem.h"

void UMyGameInstance::Init()
{
	Super::Init();

	FTickerDelegate TickDelegate = FTickerDelegate::CreateUObject(this, &UMyGameInstance::Tick);
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);

	//IPlatformInputDeviceMapper::Get().GetOnInputDeviceConnectionChange().AddUObject(this, &UMyGameInstance::OnControllerChanged);

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::BeginLoadingScreen);

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMyGameInstance::EndLoadingScreen);

	/*if (UAutoSaveSubsystem* AutoSaveSubsystem = GetSubsystem<UAutoSaveSubsystem>())
	{
		AutoSaveSubsystem->SaveNotificationWidgetClass = SaveNotificationWidgetClass;

		AutoSaveSubsystem->LoadGame();

		bisMusicMuted = AutoSaveSubsystem->GetIsMuted();
	}*/
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

bool UMyGameInstance::Tick(float DeltaSeconds)
{
	if (GEngine)
	{
		FString message = FString::Printf(TEXT("Active Controller ID: %d"), ActiveControllerID);

		GEngine->AddOnScreenDebugMessage(1, 0.2f, FColor::Blue, *message);
	}

	return true;
}

void UMyGameInstance::SetActiveControllerID(int32 ControllerID)
{
	ActiveControllerID = ControllerID;
}

int32 UMyGameInstance::GetActiveControllerID()
{
	return ActiveControllerID;
}

void UMyGameInstance::BeginLoadingScreen(const FString& MapName)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::BeginLoadingScreen: %s"), *MapName);

	const UWorld* World = GetWorld();
	if (World)
	{
		UCustomGameViewportClient* GameViewportClient = Cast<UCustomGameViewportClient>(World->GetGameViewport());
		if (GameViewportClient)
		{
			GameViewportClient->Fade(true);
		}
	}

	FLoadingScreenModule* LoadingScreenModule = FModuleManager::LoadModulePtr<FLoadingScreenModule>("LoadingScreenModule");
	if (LoadingScreenModule != nullptr)
	{
		LoadingScreenModule->StartLoadingScreen(MapName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::BeginLoadingScreen: LoadingScreenModule not found."));
	}
}

void UMyGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
	UE_LOG(LogTemp, Warning, TEXT("UMyGameInstance::EndLoadingScreen: %s"), *InLoadedWorld->GetName());

	const UWorld* World = GetWorld();
	if (World)
	{
		UCustomGameViewportClient* GameViewportClient = Cast<UCustomGameViewportClient>(World->GetGameViewport());
		if (GameViewportClient)
		{
			GameViewportClient->Fade(false);
		}
	}
}

	//UNCOMMENT WHEN CONTROLLER IS ADDED
//void UMyGameInstance::OnControllerChanged(EInputDeviceConnectionState connectionState, FPlatformUserId userID, FInputDeviceId inputrDeviceID)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Controller Changed"));
//
//	FString UserId_Text;
//	if (userID == PLATFORMUSERID_NONE)
//	{
//		UserId_Text = TEXT("None");
//	}
//	else
//	{
//		UserId_Text = FString::Printf(TEXT("%d"), userID.GetInternalId());
//	}
//
//	if (connectionState == EInputDeviceConnectionState::Disconnected)
//	{
//		FString message = FString::Printf(TEXT("Controller Connection Changed - InputDeviceID:%d, UserID:%s, Disconnected"), inputDeviceID.GetId(), *UserId_Text);
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, message);
//		UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
//	}
//	else if (connectionState == EInputDeviceConnectionState::Connected)
//	{
//		FString message = FString::Printf(TEXT("Controller Connection Changed - InputDeviceID:%d, UserID:%s, Connected"), inputDeviceID.GetId(), *UserId_Text);
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, message);
//		UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
//	}
//
//	int32 ActiveControllerID = GetActiveControllerID();
//	if (ActiveControllerID == -1)
//	{
//		return;
//	}
//
//	int32 ChangedControllerID = inputDeviceID.GetId();
//	if (ActiveControllerID + 1 == ChangedControllerID)
//	{
//		if (APlayerController* ActivePC = UMyBlueprintFunctionLibrary::GetActivePlayerController(this))
//		{
//			if (connectionState == EInputDeviceConnectionState::Connected)
//			{
//				if (ControllerDisconnectedWidget)
//				{
//					if (bDidControllerDisconnectPauseGame)
//					{
//						UGameplayStatics::SetGamePaused(this, false);
//						bDidControllerDisconnectPauseGame = false;
//					}
//					ControllerDisconnectedWidget->RemoveFromParent();
//				}
//			}
//			else
//			{
//				if (ControllerDisconnectedWidgetClass)
//				{
//					if (!UGameplayStatics::IsGamePaused(this))
//					{
//						bDidControllerDisconnectPauseGame = true;
//						UGameplayStatics::SetGamePaused(this, true);
//					}
//					ControllerDisconnectedWidget = CreateWidget<UControllerDisconnectedWidget>(ActivePC, ControllerDisconnectedWidgetClass);
//					ControllerDisconnectedWidget->AddToViewport(100);
//				}
//				else
//				{
//					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ControllerDisconnectedWidgetClass NOT Set"));
//				}
//			}
//		}
//	}
//}

void UMyGameInstance::PlayGameplayMusic()
{
	StopMenuMusic();
	StopStartScreenMusic();

	if (!bisMusicMuted)
	{
		if (GameplayMusicAudioComponent)
		{
			if (!GameplayMusicAudioComponent->IsPlaying())
			{
				GameplayMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
			}
		}
		else
		{
			if (GameplayMusic)
			{
				GameplayMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, GameplayMusic, 1, 1, 0, nullptr, true, true);

				if (GameplayMusicAudioComponent)
				{
					GameplayMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("GameplayMusic is NULL."));
			}
		}
	}
}

void UMyGameInstance::StopGameplayMusic(bool ForceStop)
{
	if (GameplayMusicAudioComponent && GameplayMusicAudioComponent->IsPlaying())
	{
		if (ForceStop)
		{
			GameplayMusicAudioComponent->Stop();
		}
		else
		{
			GameplayMusicAudioComponent->FadeOut(MusicFadeDuration, 0.0f);
		}
	}
}

void UMyGameInstance::PlayMenuMusic()
{
	StopGameplayMusic();
	StopStartScreenMusic();
	StopGameOverMusic();

	if (!bisMusicMuted)
	{
		if (MenuMusicAudioComponent)
		{
			if (!MenuMusicAudioComponent->IsPlaying())
			{
				MenuMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
			}
		}
		else
		{
			if (MenuMusic)
			{
				MenuMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, MenuMusic, 1, 1, 0, nullptr, true, true);

				if (MenuMusicAudioComponent)
				{
					MenuMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("MenuMusic is NULL."));
			}
		}
	}
}

void UMyGameInstance::StopMenuMusic(bool ForceStop)
{
	if (MenuMusicAudioComponent && MenuMusicAudioComponent->IsPlaying())
	{
		if (ForceStop)
		{
			MenuMusicAudioComponent->Stop();
		}
		else
		{
			MenuMusicAudioComponent->FadeOut(MusicFadeDuration, 0.0f);
		}
	}
}

void UMyGameInstance::PlayStartScreenMusic()
{
	StopGameplayMusic();
	StopMenuMusic();
	StopGameOverMusic();

	if (!bisMusicMuted)
	{
		if (StartScreenMusicAudioComponent)
		{
			if (!StartScreenMusicAudioComponent->IsPlaying())
			{
				StartScreenMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
			}
		}
		else
		{
			if (StartScreenMusic)
			{
				StartScreenMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, StartScreenMusic, 1, 1, 0, nullptr, true, true);

				if (StartScreenMusicAudioComponent)
				{
					StartScreenMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("StartScreenMusic is NULL."));
			}
		}
	}
}

void UMyGameInstance::StopStartScreenMusic(bool ForceStop)
{
	if (StartScreenMusicAudioComponent && StartScreenMusicAudioComponent->IsPlaying())
	{
		if (ForceStop)
		{
			StartScreenMusicAudioComponent->Stop();
		}
		else
		{
			StartScreenMusicAudioComponent->FadeOut(MusicFadeDuration, 0.0f);
		}
	}
}

void UMyGameInstance::PlayGameOverMusic()
{
	StopGameplayMusic();

	if (!bisMusicMuted)
	{
		if (GameOverScreenMusicAudioComponent)
		{
			if (!GameOverScreenMusicAudioComponent->IsPlaying())
			{
				GameOverScreenMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
			}
		}
		else
		{
			if (GameOverMusic)
			{
				GameOverScreenMusicAudioComponent = UGameplayStatics::SpawnSound2D(this, GameOverMusic, 1, 1, 0, nullptr, true, true);

				if (GameOverScreenMusicAudioComponent)
				{
					GameOverScreenMusicAudioComponent->FadeIn(MusicFadeDuration, 1.0f);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("GameOverMusic is NULL."));
			}
		}
	}
}

void UMyGameInstance::StopGameOverMusic(bool ForceStop)
{
	if (GameOverScreenMusicAudioComponent && GameOverScreenMusicAudioComponent->IsPlaying())
	{
		if (ForceStop)
		{
			GameOverScreenMusicAudioComponent->Stop();
		}
		else
		{
			GameOverScreenMusicAudioComponent->FadeOut(MusicFadeDuration, 0.0f);
		}
	}
}

void UMyGameInstance::StopAllMusic()
{
	StopMenuMusic(true);
	StopGameplayMusic(true);
	StopStartScreenMusic(true);

	bisMusicMuted = true;
}

void UMyGameInstance::EnableAllMusic()
{
	bisMusicMuted = false;
	PlayMenuMusic();
}
