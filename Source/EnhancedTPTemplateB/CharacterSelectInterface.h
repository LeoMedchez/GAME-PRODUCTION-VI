#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterSelectInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UCharacterSelectInterface : public UInterface
{
	GENERATED_BODY()
};

class ENHANCEDTPTEMPLATEB_API ICharacterSelectInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Select")
	void SetSelectedCharacter(TSubclassOf<APawn> CharacterClass);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Select")
	TSubclassOf<APawn> GetSelectedCharacter();
};
