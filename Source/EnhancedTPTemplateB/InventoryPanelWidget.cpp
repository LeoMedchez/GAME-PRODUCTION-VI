#include "InventoryPanelWidget.h"
#include "Blueprint/WidgetTree.h"

void UInventoryPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (EquipButton)
	{
		EquipButton->OnClicked.AddDynamic(this, &UInventoryPanelWidget::OnEquipButtonClicked);
	}

	if (UnequipWeaponButton)
	{
		UnequipWeaponButton->OnClicked.AddDynamic(this, &UInventoryPanelWidget::OnUnequipWeaponButtonClicked);
	}

	if (UnequipShieldButton)
	{
		UnequipShieldButton->OnClicked.AddDynamic(this, &UInventoryPanelWidget::OnUnequipShieldButtonClicked);
	}

	if (EquipButton)
	{
		EquipButton->SetIsEnabled(false);
	}

	if (UnequipWeaponButton)
	{
		UnequipWeaponButton->SetIsEnabled(false);
	}

	if (UnequipShieldButton)
	{
		UnequipShieldButton->SetIsEnabled(false);
	}
}

void UInventoryPanelWidget::RefreshInventory_Implementation()
{
	RefreshList();
	RefreshEquipmentPanel();
}

void UInventoryPanelWidget::RefreshList()
{
	if (!InventoryList || !InventorySlotClass || !InventoryComponent) return;

	InventoryList->ClearChildren();
	SelectedSlot = nullptr;
	UpdateEquipButton();

	for (int32 i = 0; i < InventoryComponent->InventoryItems.Num(); i++)
	{
		UInventorySlotWidget* SlotWidget = CreateWidget<UInventorySlotWidget>(GetWorld(), InventorySlotClass);
		if (!SlotWidget) continue;

		SlotWidget->InitInventory(InventoryComponent);
		SlotWidget->SetSlotData(InventoryComponent->InventoryItems[i], i);
		SlotWidget->OnSlotSelected.AddDynamic(this, &UInventoryPanelWidget::OnSlotSelected);

		InventoryList->AddChild(SlotWidget);
	}
}

void UInventoryPanelWidget::RefreshEquipmentPanel()
{
	if (!InventoryComponent) return;

	if (WeaponSlot)
	{
		if(InventoryComponent->EquippedWeapon.ItemName != "")
		{
			WeaponSlot->SetEquipmentSlot(InventoryComponent->EquippedWeapon, InventoryComponent->EquippedWeapon.ItemType);
		}
		else
		{
			WeaponSlot->ClearSlot();
		}
	}

	if (ShieldSlot)
	{
		if (InventoryComponent->EquippedShield.ItemName != "")
		{
			ShieldSlot->SetEquipmentSlot(InventoryComponent->EquippedShield, InventoryComponent->EquippedShield.ItemType);
		}
		else
		{
			ShieldSlot->ClearSlot();
		}
	}

	if (UnequipWeaponButton)
	{
		UnequipWeaponButton->SetIsEnabled(InventoryComponent->EquippedWeapon.ItemName != "");
	}

	if (UnequipShieldButton)
	{
		UnequipShieldButton->SetIsEnabled(InventoryComponent->EquippedShield.ItemName != "");
	}
}

void UInventoryPanelWidget::UpdateEquipButton()
{
	if (!EquipButton) return;

	EquipButton->SetIsEnabled(SelectedSlot != nullptr);
}

void UInventoryPanelWidget::OnSlotSelected(UInventorySlotWidget* SelectedSlotWidget)
{
	UE_LOG(LogTemp, Warning, TEXT("OnSlotSelected fired"));
	if (SelectedSlot && SelectedSlot != SelectedSlotWidget)
	{
		SelectedSlot->SetSelectedVisual(false);
	}

	SelectedSlot = SelectedSlotWidget;
	UpdateEquipButton();
}

void UInventoryPanelWidget::OnEquipButtonClicked()
{
	if (!SelectedSlot || !InventoryComponent) return;
	InventoryComponent->EquipItem(SelectedSlot->SlotIndex);
	SelectedSlot = nullptr;
	UpdateEquipButton();
}

void UInventoryPanelWidget::OnUnequipWeaponButtonClicked()
{
	if (!InventoryComponent) return;
	
	InventoryComponent->UnequipItem(0);
}

void UInventoryPanelWidget::OnUnequipShieldButtonClicked()
{
	if (!InventoryComponent) return;

	InventoryComponent->UnequipItem(1);
}