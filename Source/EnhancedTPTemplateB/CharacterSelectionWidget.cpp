#include "CharacterSelectionWidget.h"
#include "CharacterSelectInterface.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UCharacterSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PopulateCharacterButtons();
}

void UCharacterSelectionWidget::PopulateCharacterButtons()
{
	if (!CharacterDataTable) return;

	TArray<FCharacterData*> Rows;
	CharacterDataTable->GetAllRows<FCharacterData>(TEXT("CharacterSelectionWidget"), Rows);

	if (Rows.Num() > 0 && Rows[0])
	{
		if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
		{
			ICharacterSelectInterface::Execute_SetSelectedCharacter(GI, Rows[0]->CharacterClass);
		}
	}
}

void UCharacterSelectionWidget::OnCharacterButtonClicked(int32 CharacterIndex)
{
	if (!CharacterDataTable) return;

	TArray<FCharacterData*> Rows;
	CharacterDataTable->GetAllRows<FCharacterData>(TEXT("CharacterSelectionWidget"), Rows);

	if (Rows.IsValidIndex(CharacterIndex) && Rows[CharacterIndex])
	{
		if (UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance()))
		{
			ICharacterSelectInterface::Execute_SetSelectedCharacter(GI,
				Rows[CharacterIndex]->CharacterClass);
		}
	}
}
