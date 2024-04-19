// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/AnimalSelectionMenu.h"
#include "UserInterface/InteractionWidget.h"
#include "UserInterface/StaticWidgetBase.h"
#include "UserInterface/ScoreWidget.h"
#include "Interfaces/InteractionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Core/TreasureGameInstance.h"

AAnimalHUD::AAnimalHUD()
{
}

void AAnimalHUD::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("AnimalHUD unable to get reference to GameInstance"));

	GameInstance->OnScoreUpdated.AddDynamic(this, &AAnimalHUD::DisplayNewUnlocksWidget);

	GameInstance->OnUnlocksClaimed.AddDynamic(this, &AAnimalHUD::HideNewUnlocksWidget);

	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	} 

	if (AnimalSelectionMenuClass)
	{
		AnimalSelectionMenuWidget = CreateWidget<UAnimalSelectionMenu>(GetWorld(), AnimalSelectionMenuClass);
		AnimalSelectionMenuWidget->AddToViewport(4);
		AnimalSelectionMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (OutOfBoundsWidgetClass)
	{
		OutOfBoundsWidget = CreateWidget<UStaticWidgetBase>(GetWorld(), OutOfBoundsWidgetClass);
		OutOfBoundsWidget->AddToViewport();
		OutOfBoundsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (CrosshairClass)
	{
		Crosshair = CreateWidget<UStaticWidgetBase>(GetWorld(), CrosshairClass);
		Crosshair->AddToViewport(0);
		Crosshair->SetVisibility(ESlateVisibility::Visible);
	}

	if (NewUnlocksWidgetClass)
	{
		NewUnlocksWidget = CreateWidget<UStaticWidgetBase>(GetWorld(), NewUnlocksWidgetClass);
		NewUnlocksWidget->AddToViewport();
		NewUnlocksWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (NotEnoughSpaceWidgetClass)
	{
		NotEnoughSpaceWidget = CreateWidget<UStaticWidgetBase>(GetWorld(), NotEnoughSpaceWidgetClass);
		NotEnoughSpaceWidget->AddToViewport();
		NotEnoughSpaceWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
		ScoreWidget->AddToViewport(1);
		ScoreWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::DisplayMainMenu()
{
	if (MainMenuWidget)
	{
		bIsMainMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		HideAnimalSelectionMenu();
		HideCrosshair();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AAnimalHUD::HideMainMenu()
{
	if (MainMenuWidget)
	{
		bIsMainMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		DisplayCrosshair();
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

void AAnimalHUD::DisplayAnimalSelectionMenu()
{
	if (AnimalSelectionMenuWidget && !bIsMainMenuVisible)
	{
		bIsAnimalSelectionMenuVisible = true;
		AnimalSelectionMenuWidget->SetVisibility(ESlateVisibility::Visible);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AAnimalHUD::HideAnimalSelectionMenu()
{
	if (AnimalSelectionMenuWidget)
	{
		bIsAnimalSelectionMenuVisible = false;
		AnimalSelectionMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
}

void AAnimalHUD::DisplayInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::UpdateInteractionWidget(const FInteractableData InteractableData) const
{
	if (InteractionWidget)
	{
		InteractionWidget->UpdateWidget(InteractableData);
		DisplayInteractionWidget();
	}
}

void AAnimalHUD::DisplayOutOfBoundsWidget() const
{
	if (OutOfBoundsWidget)
	{
		OutOfBoundsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::HideOutOfBoundsWidget() const
{
	if (OutOfBoundsWidget)
	{
		OutOfBoundsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::DisplayCrosshair() const
{
	if (Crosshair)
	{
		Crosshair->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::HideCrosshair() const
{
	if (Crosshair)
	{
		Crosshair->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::DisplayNewUnlocksWidget()
{
	if (NewUnlocksWidget)
	{
		if (GameInstance->Score % 10 == 0)
		{
			NewUnlocksWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AAnimalHUD::HideNewUnlocksWidget()
{
	if (NewUnlocksWidget)
	{
		NewUnlocksWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AAnimalHUD::DisplayNotEnoughSpaceWidget() const
{
	if (NotEnoughSpaceWidget)
	{
		NotEnoughSpaceWidget->SetVisibility(ESlateVisibility::Visible);

		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle,
			this,
			&AAnimalHUD::HideNotEnoughSpaceWidget,
			1.5f,
			false);
	}
}

void AAnimalHUD::HideNotEnoughSpaceWidget() const
{
	if (NotEnoughSpaceWidget)
	{
		NotEnoughSpaceWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}


