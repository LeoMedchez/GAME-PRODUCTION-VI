#pragma once

#include "CoreMinimal.h"
#include "BasePC.h"
#include "MyPlayerController.generated.h"

class UPlayerStatWidget;
class UPlayerStats;
class UInputMappingContext;

UCLASS()
class ENHANCEDTPTEMPLATEB_API AMyPlayerController : public ABasePC
{
	GENERATED_BODY()
	
	AMyPlayerController();

protected:

	virtual void BeginPlay() override;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UPlayerStatWidget> WidgetClass;*/

	UPROPERTY(EditAnywhere, Category = "Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContext;

	virtual void SetupInputComponent() override;

//private:
//
//	UPROPERTY()
//	UPlayerStatWidget* StatWidget;
};
