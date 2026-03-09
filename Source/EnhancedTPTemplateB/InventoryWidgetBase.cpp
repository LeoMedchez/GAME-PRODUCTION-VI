#include "InventoryWidgetBase.h"

void UInventoryWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryWidgetBase::InitInventory(UInventoryComponent* InventoryComp)
{
	if (!InventoryComp) return;

	InventoryComponent = InventoryComp;

	InventoryComponent->OnInventoryChanged.AddDynamic(this, &UInventoryWidgetBase::OnInventoryChanged);
	InventoryComponent->OnItemEquipped.AddDynamic(this, &UInventoryWidgetBase::OnItemEquipped);

	RefreshInventory();
}

void UInventoryWidgetBase::RefreshInventory_Implementation()
{
}

void UInventoryWidgetBase::OnInventoryChanged()
{
	RefreshInventory_Implementation();
}

void UInventoryWidgetBase::OnItemEquipped(FItemData EquippedItem, EItemType SlotType)
{
	RefreshInventory_Implementation();
}
