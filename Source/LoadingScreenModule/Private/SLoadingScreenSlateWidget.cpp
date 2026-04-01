// Fill out your copyright notice in the Description page of Project Settings.


#include "SLoadingScreenSlateWidget.h"
#include "SlateOptMacros.h"
#include "SlateExtras.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLoadingScreenSlateWidget::Construct(const FArguments& InArgs)
{
	BackgroundTexture = InArgs._BackgroundTexture;

	BackgroundBrush = MakeShareable(new FSlateBrush());
	BackgroundBrush->SetResourceObject(BackgroundTexture);

	ChildSlot
		[
			SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.HAlign(HAlign_Fill)
				[
					SNew(SImage)
						.Image(BackgroundTexture ? BackgroundBrush.Get() : nullptr)
						.ColorAndOpacity(FLinearColor::White)
				]

				+ SOverlay::Slot()\
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(10.0f)
				[
					SNew(SThrobber)
						.Visibility(EVisibility::HitTestInvisible)
						.NumPieces(10)
				]
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION