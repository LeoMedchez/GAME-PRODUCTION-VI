#include "EquipmentSlotWidget.h"

void UEquipmentSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SlotNameText)
	{
		SlotNameText->SetText(SlotLabel);
	}
}

void UEquipmentSlotWidget::SetEquipmentSlot(FItemData InItemData, EItemType InSlotType)
{
	SlotItemData = InItemData;
	SlotType = InSlotType;

	if (SlotIcon)
	{
		SlotIcon->SetBrushFromTexture(InItemData.ItemIcon);
	}
}

void UEquipmentSlotWidget::ClearSlot()
{
	SlotItemData = FItemData();

	if (SlotIcon)
	{
		SlotIcon->SetBrushFromTexture(nullptr);
	}
}