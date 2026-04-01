#include "MyBlueprintFunctionLibrary.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

bool UMyBlueprintFunctionLibrary::bIsMapLoading = false;

int32 UMyBlueprintFunctionLibrary::GetLastMaxPlayerIndex()
{
	return UMyGameInstance::MAX_CONTROLLERS - 1;
}

void UMyBlueprintFunctionLibrary::SetActiveControllerID(const UObject* WorldContextObject, int32 ControllerID)
{
	UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GameInstanceRef)
	{
		GameInstanceRef->SetActiveControllerID(ControllerID);
	}
}

int32 UMyBlueprintFunctionLibrary::GetActiveControllerID(const UObject* WorldContextObject)
{
	UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
	if (GameInstanceRef)
	{
		return GameInstanceRef->GetActiveControllerID();
	}
	return -1;
}

void UMyBlueprintFunctionLibrary::RemoveAllPlayers(const UObject* WorldContextObject)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APlayerController::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		APlayerController* PC = Cast<APlayerController>(Actor);
		if (PC)
		{
			UGameplayStatics::RemovePlayer(PC, true);
		}
	}
}

APlayerController* UMyBlueprintFunctionLibrary::GetActivePlayerController(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerControllerFromID(WorldContextObject, GetActiveControllerID(WorldContextObject));
}

ACharacter* UMyBlueprintFunctionLibrary::GetActivePlayerCharacter(const UObject* WorldContextObject)
{
	return GetActivePlayerController(WorldContextObject)->GetCharacter();
}

void UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld>& LevelToLoad, float Delay)
{
	if (bIsMapLoading)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay: Map is already loading"));
		return;
	}

	if (LevelToLoad.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay: LevelToLoad is null"));
		return;
	}

	if (UWorld* World = WorldContextObject->GetWorld())
	{
		bIsMapLoading = true;

		FTimerHandle TimerHandle;
		World->GetTimerManager().ClearTimer(TimerHandle);

		World->GetTimerManager().SetTimer(TimerHandle, [World, LevelToLoad]()
			{
				RemoveAllPlayers(World);
				UGameplayStatics::OpenLevelBySoftObjectPtr(World, LevelToLoad);
				bIsMapLoading = false;
			}, Delay, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyBlueprintFunctionLibrary::LoadLevelByReferenceAfterDelay: World is null"));
	}
}

void UMyBlueprintFunctionLibrary::QuitAfterDelay(const UObject* WorldContextObject, float Delay)
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		FTimerHandle TimerHandle;
		World->GetTimerManager().SetTimer(TimerHandle, [World]()
			{
				UKismetSystemLibrary::QuitGame(World, nullptr, EQuitPreference::Quit, false);
			}, Delay, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMyBlueprintFunctionLibrary::QuitAfterDelay: World is null"));
	}
}

	//UNCOMMENT WHEN CONTROLLERS GETS ADDED
//UUIDataAsset* UMyBlueprintFunctionLibrary::GetUIDataAsset(const UObject* WorldContextObject)
//{
//	const UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObject));
//
//	if (!GameInstance) return nullptr;
//
//	return GameInstance->GetUIDataAsset();
//}