// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

// Forward Declarations
class UButton;
class UEditableTextBox;
class URadialSlider;
class UTreasureGameInstance;
class AAnimalHUD;

/**
 * 
 */
UCLASS()
class CRYSTANIMALS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> PerishButton = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> HowToPlayButton = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> CreditsButton = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ResetButton = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ExitButton = nullptr;


	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<URadialSlider> MasterVolumeSlider = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<URadialSlider> MusicVolumeSlider = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<URadialSlider> SFXVolumeSlider = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundMix> MasterSoundMix = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundMix> MusicSoundMix = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundMix> SFXSoundMix = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundClass> MasterSoundClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundClass> MusicSoundClass = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundClass> SFXSoundClass = nullptr;


	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UEditableTextBox> MouseSensBox = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> ButtonClickSound = nullptr;

	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	UPROPERTY()
	TObjectPtr<AAnimalHUD> HUD = nullptr;

	UFUNCTION()
	void Perish();
	UFUNCTION()
	void OpenHowToPlayPage();
	UFUNCTION()
	void OpenCreditsPage();
	UFUNCTION()
	void ResetGameProgress();
	UFUNCTION()
	void ExitGame();
	UFUNCTION()
	void ChangeMasterVolume(float Value);
	UFUNCTION()
	void ChangeMusicVolume(float Value);
	UFUNCTION()
	void ChangeSFXVolume(float Value);
	UFUNCTION()
	void ChangeMouseSens(const FText& NewText, ETextCommit::Type CommitType);
	UFUNCTION()
	void HandleMouseSensTextChanged(const FText& Text);
	UFUNCTION()
	void MouseCaptureEnded();
	
	virtual void NativeConstruct() override;
};
