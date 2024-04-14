// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/InteractionWidget.h"
#include "Interfaces/InteractionInterface.h"
#include "Components/TextBlock.h"

void UInteractionWidget::UpdateWidget(const FInteractableData InteractableData) const
{
	ActionText->SetText(InteractableData.Action);
	NameText->SetText(InteractableData.Name);
}

