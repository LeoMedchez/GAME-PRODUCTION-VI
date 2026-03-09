#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "InventoryWidgetBase.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UInventoryWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InitInventory(UInventoryComponent* InventoryComp);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory")
	void RefreshInventory();

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;

	UFUNCTION()
	void OnInventoryChanged();

	UFUNCTION()
	void OnItemEquipped(FItemData EquippedItem, EItemType SlotType);
};
