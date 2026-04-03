#include "CustomButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "MyBlueprintFunctionLibrary.h"

void UCustomButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ButtonTextValue.IsEmptyOrWhitespace())
	{
		ButtonTextValue = FText::FromString("Button");
	}

	ButtonText->SetText(ButtonTextValue);
}

void UCustomButton::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocused = false;
	DefaultStyle = Button->GetStyle();
}

void UCustomButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (APlayerController* PlayerController = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld()))
	{
		if (Button->HasUserFocus(PlayerController) && !bIsFocused)
		{
			bIsFocused = true;
			Button->SetStyle(FocusedStyle);

			PlaySound();
		}
		else if (!Button->HasUserFocus(PlayerController) && bIsFocused)
		{
			bIsFocused = false;
			Button->SetStyle(DefaultStyle);
		}
	}
}

void UCustomButton::PlaySound()
{
	if (!FocusSound)
		return;

	if (bPlayFirstFocusSound)
	{
		UGameplayStatics::PlaySound2D(this, FocusSound);
	}
	else
	{
		bPlayFirstFocusSound = true;
	}
}