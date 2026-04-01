#pragma once

#include "CoreMinimal.h"
#include "BasePC.h"
#include "StartPC.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API AStartPC : public ABasePC
{
	GENERATED_BODY()
	
public:
	virtual bool InputKey(const FInputKeyEventArgs& Params) override;

	UPROPERTY(EditDefaultsOnly)
	const TSoftObjectPtr<UWorld> NextLevel;
};
