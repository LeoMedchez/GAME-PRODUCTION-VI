#include "MyCustomCharacter.h"
#include "GameHUD.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCustomCharacter::AMyCustomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCustomCharacter::DoPause()
{
	if (!IsPaused())
	{
		Pause();
	}
	else
	{
		UnPause();
	}
}

bool AMyCustomCharacter::IsPaused() const
{
	return UGameplayStatics::IsGamePaused(GetWorld());
}

void AMyCustomCharacter::Pause()
{
	if (APlayerController* PC = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld()))
	{
		AGameHUD* GameHUD = Cast<AGameHUD>(PC->GetHUD());

		if (GameHUD)
		{
			GameHUD->ShowPauseMenu();

			PC->SetPause(true);

			FInputModeGameAndUI InputMode;
			PC->SetInputMode(InputMode);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No GameHUD Found To Show The Pause Menu"));
		}
	}
}

void AMyCustomCharacter::UnPause()
{
	if (GetWorld())
	{
		if (APlayerController* PC = UMyBlueprintFunctionLibrary::GetActivePlayerController(GetWorld()))
		{
			AGameHUD* GameHUD = Cast<AGameHUD>(PC->GetHUD());

			if (GameHUD)
			{
				GameHUD->HidePauseMenu();

				PC->SetPause(false);

				FInputModeGameOnly InputMode;
				PC->SetInputMode(InputMode);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No GameHUD Found To Hide The Pause Menu"));
			}
		}
	}
}

void AMyCustomCharacter::Back()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("AMyCustomCharacter::Back"));
	if (IsPaused())
	{
		UnPause();
	}
}