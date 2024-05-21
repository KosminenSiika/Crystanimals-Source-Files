// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/EditableNotificationWidget.h"
#include "Components/TextBlock.h"

void UEditableNotificationWidget::UpdateNotificationText(FString TextToDisplay)
{
	NotificationText->SetText(FText::FromString(TextToDisplay));
}
