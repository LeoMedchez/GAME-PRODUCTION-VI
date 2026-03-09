#include "InventorySlotWidget.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotButton)
	{
		SlotButton->OnClicked.AddDynamic(this, &UInventorySlotWidget::OnSlotButtonClicked);
	}
}

void UInventorySlotWidget::SetSlotData(FItemData InItemData, int32 InSlotIndex)
{
	SlotItemData = InItemData;
	SlotIndex = InSlotIndex;

	if (ItemIconImage && InItemData.ItemIcon)
	{
		ItemIconImage->SetBrushFromTexture(InItemData.ItemIcon);
	}
	
	if (EquippedIndicator)
	{
		EquippedIndicator->SetVisibility(InItemData.bIsEquipped ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}

	if (ItemDamageText)
	{
		ItemDamageText->SetText(FText::AsNumber(InItemData.ItemDamage));
	}

	if (ItemQuantityText)
	{
		ItemQuantityText->SetText(FText::AsNumber(InItemData.ItemQuantity));
	}

	if (ItemNameText)
	{
		ItemNameText->SetText(FText::FromString(InItemData.ItemName));
	}
}

void UInventorySlotWidget::ClearSlot()
{
	SlotItemData = FItemData();

	if (ItemIconImage)
	{
		ItemIconImage->SetBrushFromTexture(nullptr);
	}

	if (ItemNameText)
	{
		ItemNameText->SetText(FText::GetEmpty());
	}

	if (ItemQuantityText)
	{
		ItemQuantityText->SetText(FText::GetEmpty());
	}

	if (ItemDamageText)
	{
		ItemDamageText->SetText(FText::GetEmpty());
	}
}

void UInventorySlotWidget::OnSlotButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Slot clicked: %s"), *SlotItemData.ItemName);

	if (!InventoryComponent) return;

	SetSelectedVisual(true);
	OnSlotSelected.Broadcast(this);
}

void UInventorySlotWidget::SetSelectedVisual_Implementation(bool bSelcted)
{
	bIsSelected = bSelcted;
}