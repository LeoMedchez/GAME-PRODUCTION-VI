#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::AddItemToInventory(FItemData NewItem)
{
	if (InventoryItems.Num() >= MaxInventorySize) return;

	InventoryItems.Add(NewItem);
	OnInventoryChanged.Broadcast();
}

void UInventoryComponent::RemoveItemFromInventory(int32 slotIndex)
{
	if (!InventoryItems.IsValidIndex(slotIndex)) return;

	InventoryItems.RemoveAt(slotIndex);
	OnInventoryChanged.Broadcast();
}

void UInventoryComponent::EquipItem(int32 slotIndex)
{
    if (!InventoryItems.IsValidIndex(slotIndex)) return;

    FItemData ItemToEquip = InventoryItems[slotIndex];

    if (ItemToEquip.ItemType == EItemType::Shield)
    {
        if (!CheckShieldCompability(EquippedWeapon)) return;

        // Move existing shield back to inventory first
        if (EquippedShield.ItemName != "")
        {
            EquippedShield.bIsEquipped = false;
            InventoryItems.Add(EquippedShield);
        }

        EquippedShield = ItemToEquip;
        EquippedShield.bIsEquipped = true;
    }
    else
    {
        if (!ItemToEquip.bCanUseWithShield && EquippedShield.ItemName != "")
        {
            UnequipItem(slotIndex);
        }

        // Move existing weapon back to inventory first
        if (EquippedWeapon.ItemName != "")
        {
            EquippedWeapon.bIsEquipped = false;
            InventoryItems.Add(EquippedWeapon);
        }

        EquippedWeapon = ItemToEquip;
        EquippedWeapon.bIsEquipped = true;
    }

    InventoryItems.RemoveAt(slotIndex);
    OnItemEquipped.Broadcast(ItemToEquip, ItemToEquip.ItemType);
    OnInventoryChanged.Broadcast();
}

void UInventoryComponent::UnequipItem(int32 slotIndex)
{
	if (InventoryItems.Num() >= MaxInventorySize) return;

	if (slotIndex == 0 && EquippedWeapon.ItemName != "")
	{
		EquippedWeapon.bIsEquipped = false;
		InventoryItems.Add(EquippedWeapon);
		EquippedWeapon = FItemData();
	}
	else if (slotIndex == 1 && EquippedShield.ItemName != "")
	{
		EquippedShield.bIsEquipped = false;
		InventoryItems.Add(EquippedShield);
		EquippedShield = FItemData();
	}

	OnInventoryChanged.Broadcast();
}

FItemData UInventoryComponent::GetItemSlot(int32 SlotIndex)
{
	if (!InventoryItems.IsValidIndex(SlotIndex)) return FItemData();
	return InventoryItems[SlotIndex];
}

bool UInventoryComponent::CheckShieldCompability(FItemData ItemToCheck)
{
	return ItemToCheck.bCanUseWithShield;
}
