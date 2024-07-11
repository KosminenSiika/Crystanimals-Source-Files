// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/RadialSlider.h"
#include "Core/TreasureGameInstance.h"
#include "UserInterface/AnimalHUD.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("MainMenu unable to get reference to GameInstance"));

	HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AAnimalHUD>();
	checkf(HUD, TEXT("MainMenu unable to get reference to HUD"));

	if (PerishButton)
	{
		PerishButton->OnClicked.AddDynamic(this, &UMainMenu::Perish);
	}

	if (HowToPlayButton)
	{
		HowToPlayButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHowToPlayPage);
	}

	if (CreditsButton)
	{
		CreditsButton->OnClicked.AddDynamic(this, &UMainMenu::OpenCreditsPage);
	}

	if (ResetButton)
	{
		ResetButton->OnClicked.AddDynamic(this, &UMainMenu::ResetGameProgress);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);
	}

	if (MasterVolumeSlider)
	{
		MasterVolumeSlider->SetValue(GameInstance->MasterVolume);
		ChangeMasterVolume(GameInstance->MasterVolume);

		MasterVolumeSlider->OnValueChanged.AddDynamic(this, &UMainMenu::ChangeMasterVolume);
		MasterVolumeSlider->OnMouseCaptureEnd.AddDynamic(this, &UMainMenu::MouseCaptureEnded);
	}

	if (MusicVolumeSlider)
	{
		MusicVolumeSlider->SetValue(GameInstance->MusicVolume);
		ChangeMusicVolume(GameInstance->MusicVolume);

		MusicVolumeSlider->OnValueChanged.AddDynamic(this, &UMainMenu::ChangeMusicVolume);
		MusicVolumeSlider->OnMouseCaptureEnd.AddDynamic(this, &UMainMenu::MouseCaptureEnded);
	}

	if (SFXVolumeSlider)
	{
		SFXVolumeSlider->SetValue(GameInstance->SFXVolume);
		ChangeSFXVolume(GameInstance->SFXVolume);

		SFXVolumeSlider->OnValueChanged.AddDynamic(this, &UMainMenu::ChangeSFXVolume);
		SFXVolumeSlider->OnMouseCaptureEnd.AddDynamic(this, &UMainMenu::MouseCaptureEnded);
	}

	if (MouseSensBox)
	{
		MouseSensBox->SetText(FText::FromString(FString::SanitizeFloat(GameInstance->MouseSens)));
		MouseSensBox->OnTextCommitted.AddDynamic(this, &UMainMenu::ChangeMouseSens);
	}
}


void UMainMenu::Perish()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	HUD->DisplayConfirmationWidget("unalive yourself");
}

void UMainMenu::OpenHowToPlayPage()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	HUD->DisplayHowToPlayPage();
}

void UMainMenu::OpenCreditsPage()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	HUD->DisplayCreditsPage();
}

void UMainMenu::ResetGameProgress()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	HUD->DisplayConfirmationWidget("reset the whole game");
}

void UMainMenu::ExitGame()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	HUD->DisplayConfirmationWidget("exit the game");
}

void UMainMenu::ChangeMasterVolume(float Value)
{
	GameInstance->MasterVolume = Value;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, MasterSoundClass, Value, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);
}

void UMainMenu::ChangeMusicVolume(float Value)
{
	GameInstance->MusicVolume = Value;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MusicSoundMix, MusicSoundClass, Value, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), MusicSoundMix);
}

void UMainMenu::ChangeSFXVolume(float Value)
{
	GameInstance->SFXVolume = Value;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SFXSoundMix, SFXSoundClass, Value, 1.0f, 0.0f);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SFXSoundMix);
}

void UMainMenu::ChangeMouseSens(const FText& NewText, ETextCommit::Type TextType)
{
	if (MouseSensBox->GetText().ToString().IsNumeric())
	{
		GameInstance->MouseSens = FCString::Atof(*(MouseSensBox->GetText().ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inputted text wasn't numeric"));
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
		GameInstance->SaveOnlySettings();
	}
	
}

void UMainMenu::MouseCaptureEnded()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	GameInstance->SaveOnlySettings();
}

