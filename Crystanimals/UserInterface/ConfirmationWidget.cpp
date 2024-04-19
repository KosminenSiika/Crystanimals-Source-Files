// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ConfirmationWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Core/TreasureGameInstance.h"

void UConfirmationWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("ConfirmationWidget unable to get reference to GameInstance"));

	if (YesButton)
	{
		YesButton->OnClicked.AddDynamic(this, &UConfirmationWidget::ConfirmAction);
	}
	if (NoButton)
	{
		NoButton->OnClicked.AddDynamic(this, &UConfirmationWidget::CancelAction);
	}
}


void UConfirmationWidget::SetAction(FString ActionToSet)
{
	Action->SetText(FText::FromString(ActionToSet));
}

void UConfirmationWidget::ConfirmAction()
{
	if (Action)
	{
		if (Action->GetText().ToString() == "exit the game")
		{
			GameInstance->ExitGame();
		}
		if (Action->GetText().ToString() == "reset game progress")
		{
			GameInstance->ResetGame();
		}
	}
}

void UConfirmationWidget::CancelAction()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}

