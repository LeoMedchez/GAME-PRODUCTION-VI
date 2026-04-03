#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Blueprint/UserWidget.h"
#include "UIDataAsset.generated.h"

UENUM()
enum class EIconType : uint8
{
	Select,
	Back,
};

UCLASS()
class ENHANCEDTPTEMPLATEB_API UUIDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> SelectIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Icons", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> BackIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> ControllerWidget;

public:

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon(EIconType IconType) const;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UUserWidget> GetControlsWidget() const { return ControllerWidget; }
};
