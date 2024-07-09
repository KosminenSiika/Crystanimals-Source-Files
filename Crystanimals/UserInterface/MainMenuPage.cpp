// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenuPage.h"
#include "Components/Button.h"
#include "UserInterface/AnimalHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Core/TreasureGameInstance.h"
#include "Player/AnimalPlayerController.h"

void UMainMenuPage::NativeConstruct()
{
	Super::NativeConstruct();

	if (OkButton)
	{
		OkButton->OnClicked.AddDynamic(this, &UMainMenuPage::ClosePage);
	}
}

void UMainMenuPage::ClosePage()
{
	UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickSound);
	
	if (UGameplayStatics::DoesSaveGameExist("SaveSlot1", 0))
	{
		GetWorld()->GetFirstPlayerController()->GetHUD<AAnimalHUD>()->HideMainMenuPages();
	} 
	else
	{
		GetGameInstance<UTreasureGameInstance>()->SaveGame();
		GetWorld()->GetFirstPlayerController<AAnimalPlayerController>()->HandleOpenCloseMainMenu();
	}
}