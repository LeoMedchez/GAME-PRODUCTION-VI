#pragma once

#include "CoreMinimal.h"
#include "BaseGM.h"
#include "GameGM.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API AGameGM : public ABaseGM
{
	GENERATED_BODY()
	
public:

	AGameGM();

	virtual void StartPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	UPROPERTY(EditDefaultsOnly, Category = "Character Select")
	TSubclassOf<APawn> DefaulfCharacterClass;
};
