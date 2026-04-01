#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class LOADINGSCREENMODULE_API SLoadingScreenSlateWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingScreenSlateWidget)
		: _BackgroundTexture(nullptr)
		{
		}
		SLATE_ARGUMENT(UTexture2D*, BackgroundTexture)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	UTexture2D* BackgroundTexture;

	TSharedPtr<FSlateBrush> BackgroundBrush;
};
