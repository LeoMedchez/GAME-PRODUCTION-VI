#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePC.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API ABasePC : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual bool InputKey(const FInputKeyEventArgs& Params) override;
};
