// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TreasureGameInstance.h"
#include "Player/AnimalCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Core/TreasureSaveGame.h"

void UTreasureGameInstance::Init()
{
	if (UGameplayStatics::DoesSaveGameExist("SaveSlot1", 0))
	{
		LoadSaveGame();
	}
	else
	{
		LoadDefaultDataValues();
	}
	CurrentAnimal = EAnimal::Dog;
	CurrentRealm = "HubRealm";
}

void UTreasureGameInstance::SaveGame()
{
	if (UTreasureSaveGame* SaveGameInstance = Cast<UTreasureSaveGame>(UGameplayStatics::CreateSaveGameObject(UTreasureSaveGame::StaticClass())))
	{
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		SavedDelegate.BindUObject(this, &UTreasureGameInstance::NotifyGameSaved);

		SaveGameInstance->ExistingCrystals = this->ExistingCrystals;
		SaveGameInstance->Score = this->Score;
		SaveGameInstance->CurrentAnimal = this->CurrentAnimal;
		SaveGameInstance->CurrentRealm = this->CurrentRealm;
		SaveGameInstance->bHasHeatResistance = this->bHasHeatResistance;
		SaveGameInstance->bHasColdResistance = this->bHasColdResistance;
		SaveGameInstance->bNewUnlocksNotClaimed = this->bNewUnlocksNotClaimed;
		SaveGameInstance->bHasKey = this->bHasKey;
		SaveGameInstance->bIsTrapdoorUnlocked = this->bIsTrapdoorUnlocked;
		SaveGameInstance->bIsTrapdoorOpen = this->bIsTrapdoorOpen;
		SaveGameInstance->MouseSens = this->MouseSens;
		SaveGameInstance->MasterVolume = this->MasterVolume;
		SaveGameInstance->MusicVolume = this->MusicVolume;
		SaveGameInstance->SFXVolume = this->SFXVolume;

		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "SaveSlot1", 0, SavedDelegate);
	}
}

void UTreasureGameInstance::SaveOnlySettings()
{
	if (UTreasureSaveGame* LoadedGame = Cast<UTreasureSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot1", 0)))
	{
		if (UTreasureSaveGame* SaveGameInstance = Cast<UTreasureSaveGame>(UGameplayStatics::CreateSaveGameObject(UTreasureSaveGame::StaticClass())))
		{
			SaveGameInstance->ExistingCrystals = LoadedGame->ExistingCrystals;
			SaveGameInstance->Score = LoadedGame->Score;
			SaveGameInstance->CurrentAnimal = LoadedGame->CurrentAnimal;
			SaveGameInstance->CurrentRealm = LoadedGame->CurrentRealm;
			SaveGameInstance->bHasHeatResistance = LoadedGame->bHasHeatResistance;
			SaveGameInstance->bHasColdResistance = LoadedGame->bHasColdResistance;
			SaveGameInstance->bNewUnlocksNotClaimed = LoadedGame->bNewUnlocksNotClaimed;
			SaveGameInstance->bHasKey = LoadedGame->bHasKey;
			SaveGameInstance->bIsTrapdoorUnlocked = LoadedGame->bIsTrapdoorUnlocked;
			SaveGameInstance->bIsTrapdoorOpen = LoadedGame->bIsTrapdoorOpen;
			SaveGameInstance->MouseSens = this->MouseSens;
			SaveGameInstance->MasterVolume = this->MasterVolume;
			SaveGameInstance->MusicVolume = this->MusicVolume;
			SaveGameInstance->SFXVolume = this->SFXVolume;

			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "SaveSlot1", 0);

			UE_LOG(LogTemp, Warning, TEXT("Settings saved successfully :)"))
		}
	}
}

void UTreasureGameInstance::LoadSaveGame()
{
	if (UTreasureSaveGame* LoadedGame = Cast<UTreasureSaveGame>(UGameplayStatics::LoadGameFromSlot("SaveSlot1", 0)))
	{
		this->ExistingCrystals = LoadedGame->ExistingCrystals;
		this->Score = LoadedGame->Score;
		this->CurrentAnimal = LoadedGame->CurrentAnimal;
		this->CurrentRealm = LoadedGame->CurrentRealm;
		this->bHasHeatResistance = LoadedGame->bHasHeatResistance;
		this->bHasColdResistance = LoadedGame->bHasColdResistance;
		this->bNewUnlocksNotClaimed = LoadedGame->bNewUnlocksNotClaimed;
		this->bHasKey = LoadedGame->bHasKey;
		this->bIsTrapdoorUnlocked = LoadedGame->bIsTrapdoorUnlocked;
		this->bIsTrapdoorOpen = LoadedGame->bIsTrapdoorOpen;
		this->MouseSens = LoadedGame->MouseSens;
		this->MasterVolume = LoadedGame->MasterVolume;
		this->MusicVolume = LoadedGame->MusicVolume;
		this->SFXVolume = LoadedGame->SFXVolume;
	}
	UE_LOG(LogTemp, Warning, TEXT("Loaded last save"));
}

void UTreasureGameInstance::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void UTreasureGameInstance::NotifyGameSaved(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess)
	{
		OnGameSaved.Broadcast();
	}
}

void UTreasureGameInstance::LoadDefaultDataValues()
{
	ExistingCrystals =
	{
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
		"11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
		"21", "22", "23", "24", "25", "26", "27", "28", "29", "30",
		"31", "32", "33", "34", "35", "36", "37", "38", "39", "40",
		"41", "42", "43", "44", "45", "46", "47", "48", "49", "50",
		"51", "52", "53", "54", "55", "56", "57", "58", "59", "60",
		"61", "62", "63", "64", "65", "66", "67", "68", "69", "70",
		"71", "72", "73", "74", "75", "76", "77", "78", "79", "80"
	};
	Score = 0;
	CurrentAnimal = EAnimal::Dog;
	CurrentRealm = "HubRealm";
	bHasHeatResistance = false;
	bHasColdResistance = false;
	bNewUnlocksNotClaimed = false;
	bHasKey = false;
	bIsTrapdoorUnlocked = false;
	bIsTrapdoorOpen = false;
	MouseSens = 1.0f;
	MasterVolume = 1.0f;
	MusicVolume = 1.0f;
	SFXVolume = 1.0f;
	bShouldSaveAfterRealmChange = false;

	UE_LOG(LogTemp, Warning, TEXT("No save file found, default TreasureGameInstance values loaded"));
}

void UTreasureGameInstance::ResetGame()
{
	UGameplayStatics::DeleteGameInSlot("SaveSlot1", 0);
	LoadDefaultDataValues();
	UGameplayStatics::OpenLevel(this, "HubRealm");
	UE_LOG(LogTemp, Warning, TEXT("Game Progress has been reset"));
}

void UTreasureGameInstance::ChangeRealm(FName RealmName)
{
	CurrentRealm = RealmName;
	UGameplayStatics::OpenLevel(this, RealmName);
}
