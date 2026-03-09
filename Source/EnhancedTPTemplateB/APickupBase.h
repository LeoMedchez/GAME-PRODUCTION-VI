#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryComponent.h"
#include "APickupBase.generated.h"

UCLASS()
class ENHANCEDTPTEMPLATEB_API AAPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPickupBase();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Data")
	FItemData ItemData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
