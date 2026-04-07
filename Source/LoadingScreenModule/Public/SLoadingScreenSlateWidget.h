#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class LOADINGSCREENMODULE_API SLoadingScreenSlateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingScreenSlateWidget)
		: _ImageSwitchInterval(3.0f)
		{
		}
		SLATE_ARGUMENT(TArray<UTexture2D*>, BackgroundTextures)
		SLATE_ARGUMENT(float, ImageSwitchInterval)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime,
		const float InDeltaTime) override;

private:

	void UpdateBackgroundImage();

	TArray<UTexture2D*> BackgroundTextures;
	TSharedPtr<FSlateBrush> BackgroundBrush;
	TSharedPtr<SImage> BackgroundImage;

	int32 CurrentImageIndex = 0;
	float ImageSwitchInterval = 3.0f;
	float TimeSinceLastSwitch = 0.0f;
};
