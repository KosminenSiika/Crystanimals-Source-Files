// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/FreezeOverlayWidget.h"
#include "Components/Image.h"

void UFreezeOverlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OverlayImage->SetOpacity(0.0f);
}


void UFreezeOverlayWidget::SetOverlayOpacity(float InOpacity)
{
	OverlayImage->SetOpacity(InOpacity);
}

void UFreezeOverlayWidget::FadeOpacityToZero(float InOpacity)
{
	MaxOpacity = InOpacity;

	GetWorld()->GetTimerManager().SetTimer(FadeTimer,
		this,
		&UFreezeOverlayWidget::UpdateOpacity,
		0.05f,
		true);

	FadeStartTime = GetWorld()->GetTimeSeconds();
}

void UFreezeOverlayWidget::UpdateOpacity()
{
	float ElapsedTime = GetWorld()->TimeSince(FadeStartTime);

	if (ElapsedTime >= 0.5f)
	{
		GetWorld()->GetTimerManager().ClearTimer(FadeTimer);
		OverlayImage->SetOpacity(0.0f);
	}
	else
	{
		OverlayImage->SetOpacity((1.0f - ElapsedTime / 0.5f) * MaxOpacity);
	}
}
