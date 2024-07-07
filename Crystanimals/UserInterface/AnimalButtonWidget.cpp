// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/AnimalButtonWidget.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Player/AnimalCharacter.h"
#include "Player/AnimalPlayerController.h"
#include "Kismet/GameplayStatics.h"

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

		if (PlayerController->GetPawn<AAnimalCharacter>()->SwitchAnimal(DesiredAnimal))
		{
			UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
		}
	}
}

void UAnimalButtonWidget::ToggleHittable(bool IsHittable)
{
	if (IsHittable)
	{
		AnimalButton->SetVisibility(ESlateVisibility::Visible);
		GreyMask->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		AnimalButton->SetVisibility(ESlateVisibility::HitTestInvisible);
		GreyMask->SetVisibility(ESlateVisibility::Visible);
	}
}

