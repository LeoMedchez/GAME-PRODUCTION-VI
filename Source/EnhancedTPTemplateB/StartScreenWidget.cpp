#include "StartScreenWidget.h"

void UStartScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(TextFade, 0, 0, EUMGSequencePlayMode::Forward, 1);
	PlayAnimation(MovingObject, 0, 0, EUMGSequencePlayMode::Forward, 0.5);
}