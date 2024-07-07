// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/AnimalButtonWidget.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Player/AnimalCharacter.h"
#include "Player/AnimalPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UserInterface/AnimalHUD.h"

void UAnimalButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<AAnimalPlayerController>(GetWorld()->GetFirstPlayerController());
	checkf(PlayerController, TEXT("AnimalButtonWidget could not get a reference to the PlayerController"));

	if (AnimalButton)
	{
		AnimalButton->OnClicked.AddDynamic(this, &UAnimalButtonWidget::SwitchToAnimal);
	}
}

void UAnimalButtonWidget::SwitchToAnimal()
{
	if (PlayerController)
	{
		PlayerController->HandleCloseAnimalSelectionMenu();

		if (PlayerController->GetPawn<AAnimalCharacter>()->GetCharacterMovement()->IsFalling())
		{
			PlayerController->GetHUD<AAnimalHUD>()->DisplayCannotChangeWhileFallingWidget();
		}
		else
		{
			UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
			PlayerController->GetPawn<AAnimalCharacter>()->SwitchAnimal(DesiredAnimal);
		}
	}
}

void UAnimalButtonWidget::SetGreyMaskVisibility(bool ShouldBeVisible)
{
	if (ShouldBeVisible)
	{
		GreyMask->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GreyMask->SetVisibility(ESlateVisibility::Collapsed);
	}
}

