#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Sword UMETA(DisplayName = "Sword"),
	Shield UMETA(DisplayName = "Shield"),
	Bow UMETA(DisplayName = "Bow"),
	Magic UMETA(DisplayName = "Magic"),
	Consumable UMETA(DisplayName = "Consumable"),
	Quest UMETA(DisplayName = "Quest"),
	Misc UMETA(DisplayName = "Misc"),
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemName = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ItemDamage = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ItemQuantity = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> WeaponClass = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemType ItemType = EItemType::Misc;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanUseWithShield = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsEquipped = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TSubclassOf<UAnimInstance> AttackAnimClass = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* AttackAnimA = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* AttackAnimB = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* AttackAnimC = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* WeaponDrawAnim = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* WeaponSheatheAnim = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FName SheathSocket = NAME_None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FName EquippedSocket = NAME_None;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemEquipped, FItemData, EquippedItem, EItemType, slotType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENHANCEDTPTEMPLATEB_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	FItemData EquippedWeapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	FItemData EquippedShield;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	TArray<FItemData> InventoryItems;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToInventory(FItemData NewItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemFromInventory(int32 slotIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void EquipItem(int32 slotIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UnequipItem(int32 slotIndex);

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemEquipped OnItemEquipped;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FItemData GetItemSlot(int32 SlotIndex);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	int32 MaxInventorySize = 20;

private:

	bool CheckShieldCompability(FItemData ItemToCheck);
};