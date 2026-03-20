#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "EquipmentSlotWidget.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API UEquipmentSlotWidget : public UInventoryWidgetBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetEquipmentSlot(FItemData InItemData, EItemType InSlotType);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void ClearSlot();

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	EItemType SlotType;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	FItemData SlotItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (ExposeOnSpawn = "true"))
	FText SlotLabel = FText::FromString("Slot");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	UTexture2D* EmptySlotTexture;

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UImage* SlotIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotNameText;
};
