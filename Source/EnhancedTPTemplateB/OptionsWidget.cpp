#include "OptionsWidget.h"
#include "MyBlueprintFunctionLibrary.h"
#include "CustomButton.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "AutoSaveSubsystem.h"

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MuteMusicButton)
	{
		MuteMusicButton->GetButton()->SetFocus();
		MuteMusicButton->SetPlayFirstFocusSound(false);
		MuteMusicButton->GetButton()->OnClicked.AddDynamic(this, &UOptionsWidget::OnMuteMusicButtonClicked);

		if (EnableMusicButton)
		{
			EnableMusicButton->GetButton()->OnClicked.AddDynamic(this, &UOptionsWidget::OnEnableMusicButtonClicked);
		}

		SetIsFocusable(true);
	}

}

void UOptionsWidget::OnMuteMusicButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Mute Music Button Clicked"));
	UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstanceRef)
	{
		GameInstanceRef->StopAllMusic();
	}

	if (UAutoSaveSubsystem* AutoSaveSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAutoSaveSubsystem>())
	{
		AutoSaveSubsystem->SetIsMuted(true);
	}
}

void UOptionsWidget::OnEnableMusicButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Enable Music Button Clicked"));
	UMyGameInstance* GameInstanceRef = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GameInstanceRef)
	{
		GameInstanceRef->EnableAllMusic();
	}

	if (UAutoSaveSubsystem* AutoSaveSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UAutoSaveSubsystem>())
	{
		AutoSaveSubsystem->SetIsMuted(false);
	}
}