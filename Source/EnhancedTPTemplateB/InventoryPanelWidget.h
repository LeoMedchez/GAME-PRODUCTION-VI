#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetBase.h"
#include "InventorySlotWidget.h"
#include "Components/ScrollBox.h"
#include "CustomButton.h"
#include "EquipmentSlotWidget.h"
#include "InventoryPanelWidget.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UInventoryPanelWidget : public UInventoryWidgetBase
{
	GENERATED_BODY()
	
public:

	virtual void RefreshInventory_Implementation() override;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* InventoryList;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlotWidget* WeaponSlot;

	UPROPERTY(meta = (BindWidget))
	UEquipmentSlotWidget* ShieldSlot;

	UPROPERTY(meta = (BindWidget))
	UCustomButton* EquipButton;

	UPROPERTY(meta = (BindWidget))
	UCustomButton* UnequipWeaponButton;

	UPROPERTY(meta = (BindWidget))
	UCustomButton* UnequipShieldButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UInventorySlotWidget> InventorySlotClass;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	UInventorySlotWidget* SelectedSlot;

private:

	void RefreshList();
	
	void RefreshEquipmentPanel();

	void UpdateEquipButton();

	void SetInitialFocus();

	UFUNCTION()
	void OnEquipButtonClicked();

	UFUNCTION()
	void OnUnequipWeaponButtonClicked();

	UFUNCTION()
	void OnUnequipShieldButtonClicked();

private:
	FTimerHandle FocusInventoryPanelTimerHandle;

public:

	UFUNCTION()
	void OnSlotSelected(UInventorySlotWidget* SelectedSlotWidget);
};
