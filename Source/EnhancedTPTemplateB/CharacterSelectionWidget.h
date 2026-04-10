#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterData.h"
#include "CharacterSelectionWidget.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UCharacterSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
		
	void NativeConstruct() override;

private:

	UPROPERTY(EditAnywhere, Category = "Character Select", meta = (AllowPrivateAccess = "true"))
	UDataTable* CharacterDataTable;

	void PopulateCharacterButtons();

	UFUNCTION()
	void OnCharacterButtonClicked(int32  CharacterIndex);
};
