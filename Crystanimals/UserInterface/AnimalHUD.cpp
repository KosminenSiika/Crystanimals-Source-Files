// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimalHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/AnimalSelectionMenu.h"
#include "UserInterface/InteractionWidget.h"
#include "UserInterface/StaticWidgetBase.h"
#include "Interfaces/InteractionInterface.h"

AAnimalHUD::AAnimalHUD()
{
}

void AAnimalHUD::BeginPlay()
{
	Super::BeginPlay();

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
		Crosshair->AddToViewport();
		Crosshair->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (NewUnlocksWidgetClass)
	{
		NewUnlocksWidget = CreateWidget<UStaticWidgetBase>(GetWorld(), NewUnlocksWidgetClass);
		NewUnlocksWidget->AddToViewport();
		NewUnlocksWidget->SetVisibility(ESlateVisibility::Collapsed);
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
	}
}

void AAnimalHUD::HideMainMenu()
{
	if (MainMenuWidget)
	{
		bIsMainMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		DisplayCrosshair();
	}
}

void AAnimalHUD::DisplayAnimalSelectionMenu()
{
	if (AnimalSelectionMenuWidget && !bIsMainMenuVisible)
	{
		bIsAnimalSelectionMenuVisible = true;
		AnimalSelectionMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::HideAnimalSelectionMenu()
{
	if (AnimalSelectionMenuWidget)
	{
		bIsAnimalSelectionMenuVisible = false;
		AnimalSelectionMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
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

void AAnimalHUD::DisplayNewUnlocksWidget() const
{
	if (NewUnlocksWidget)
	{
		NewUnlocksWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AAnimalHUD::HideNewUnlocksWidget() const
{
	if (NewUnlocksWidget)
	{
		NewUnlocksWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}


