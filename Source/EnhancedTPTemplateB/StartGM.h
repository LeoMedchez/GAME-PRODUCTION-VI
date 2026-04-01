#pragma once

#include "CoreMinimal.h"
#include "BaseGM.h"
#include "StartGM.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API AStartGM : public ABaseGM
{
	GENERATED_BODY()
	
public:

	AStartGM();

	virtual void StartPlay() override;
};
