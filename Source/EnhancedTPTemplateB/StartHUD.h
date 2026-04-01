#pragma once

#include "CoreMinimal.h"
#include "BaseHUD.h"
#include "StartHUD.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API AStartHUD : public ABaseHUD
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> StartScreenClass;
};
