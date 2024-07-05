// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ProgressionShop.h"
#include "Core/TreasureGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProgressionShop::AProgressionShop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

}

// Called when the game starts or when spawned
void AProgressionShop::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("ProgressionShop unable to get reference to GameInstance"));

	InteractableData = InstanceInteractableData;
}

// Called every frame
void AProgressionShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProgressionShop::Interact()
{
	UGameplayStatics::PlaySound2D(GetWorld(), UnlocksClaimSound);
	GameInstance->bNewUnlocksNotClaimed = false;
	GameInstance->OnUnlocksClaimed.Broadcast();
	GameInstance->SaveGame();
}

