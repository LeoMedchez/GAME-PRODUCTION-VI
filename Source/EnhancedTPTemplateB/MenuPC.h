#pragma once

#include "CoreMinimal.h"
#include "BasePC.h"
#include "MenuPC.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API AMenuPC : public ABasePC
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "Input|Input Mappings")
	TArray<class UInputMappingContext*> DefaultMappingContexts;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	virtual bool InputKey(const FInputKeyEventArgs& Params)  override;
};
