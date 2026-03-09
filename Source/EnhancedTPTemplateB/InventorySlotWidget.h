#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "InventorySlotWidget.generated.h"
	
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotSelected, UInventorySlotWidget*, SelectedSlot);

UCLASS()
class ENHANCEDTPTEMPLATEB_API UInventorySlotWidget : public UInventoryWidgetBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnSlotSelected OnSlotSelected;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetSlotData(FItemData InItemData, int32 InSlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearSlot();

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	FItemData SlotItemData;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	int32 SlotIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	bool bIsSelected = false;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
	void SetSelectedVisual(bool bSelcted);

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemIconImage;

	UPROPERTY(meta = (BindWidget))
	UImage* EquippedIndicator;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemQuantityText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDamageText;

	UPROPERTY(meta = (BindWidget))
	UButton* SlotButton;

	UFUNCTION()
	void OnSlotButtonClicked();
};
