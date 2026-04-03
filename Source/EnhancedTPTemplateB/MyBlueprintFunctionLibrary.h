#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure, Category = "MyBlueprintFunctionLibrary")
	static int32 GetLastMaxPlayerIndex();

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void SetActiveControllerID(const UObject* WorldContextObject, int32 ControllerID);

	UFUNCTION(BlueprintPure, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static int32 GetActiveControllerID(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void RemoveAllPlayers(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static class APlayerController* GetActivePlayerController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static class ACharacter* GetActivePlayerCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void LoadLevelByReferenceAfterDelay(const UObject* WorldContextObject, const TSoftObjectPtr<UWorld>& LevelToLoad, float Delay = 0.4f);

	UFUNCTION(BlueprintCallable, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void QuitAfterDelay(const UObject* WorldContextObject, float Delay = 0.4f);

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyBlueprintFunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static class UUIDataAsset* GetUIDataAsset(const UObject* WorldContextObject);

private:

	static bool bIsMapLoading;
};
