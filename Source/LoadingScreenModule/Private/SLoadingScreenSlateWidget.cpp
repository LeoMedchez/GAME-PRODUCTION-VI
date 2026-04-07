// Fill out your copyright notice in the Description page of Project Settings.


#include "SLoadingScreenSlateWidget.h"
#include "SlateOptMacros.h"
#include "SlateExtras.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SLoadingScreenSlateWidget::Construct(const FArguments& InArgs)
{
    BackgroundTextures = InArgs._BackgroundTextures;
    ImageSwitchInterval = InArgs._ImageSwitchInterval;

    BackgroundBrush = MakeShareable(new FSlateBrush());

    if (BackgroundTextures.Num() > 0)
    {
        BackgroundBrush->SetResourceObject(BackgroundTextures[0]);
    }

    ChildSlot
        [
            SNew(SOverlay)
                + SOverlay::Slot()
                .HAlign(HAlign_Fill)
                .VAlign(VAlign_Fill)
                [
                    SAssignNew(BackgroundImage, SImage)
                        .Image(BackgroundBrush.Get())
                        .ColorAndOpacity(FLinearColor::White)
                ]
                + SOverlay::Slot()
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

void SLoadingScreenSlateWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
    SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

    if (BackgroundTextures.Num() <= 1) return;

    TimeSinceLastSwitch += InDeltaTime;

    if (TimeSinceLastSwitch >= ImageSwitchInterval)
    {
        TimeSinceLastSwitch = 0.0f;
        CurrentImageIndex = (CurrentImageIndex + 1) % BackgroundTextures.Num();
        UpdateBackgroundImage();
    }
}

void SLoadingScreenSlateWidget::UpdateBackgroundImage()
{
    if (!BackgroundTextures.IsValidIndex(CurrentImageIndex)) return;
    if (!BackgroundImage.IsValid()) return;

    BackgroundBrush->SetResourceObject(BackgroundTextures[CurrentImageIndex]);
    BackgroundImage->SetImage(BackgroundBrush.Get());
}
