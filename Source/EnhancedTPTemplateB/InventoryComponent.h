#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Engine/StaticMesh.h"
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
	FString ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ItemDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ItemQuantity;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ItemIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* ItemMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemType ItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanUseWithShield;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsEquipped = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	TSubclassOf<UAnimInstance> AttackAnimClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* AttackAnimA;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* AttackAnimB;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* AttackAnimC;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* WeaponDrawAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	UAnimMontage* WeaponSheatheAnim;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FName SheathSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	FName EquippedSocket;
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