#pragma once

#include "CoreMinimal.h"
#include "BaseGM.h"
#include "MenuGM.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API AMenuGM : public ABaseGM
{
	GENERATED_BODY()
	
public:

	AMenuGM();

	virtual void StartPlay() override;
};
