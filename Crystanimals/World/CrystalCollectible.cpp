// Fill out your copyright notice in the Description page of Project Settings.


#include "World/CrystalCollectible.h"
#include "Core/TreasureGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACrystalCollectible::ACrystalCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

}

// Called when the game starts or when spawned
void ACrystalCollectible::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("CrystalCollectible unable to get reference to GameInstance"));

	if (CrystalID.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("CrystalID has not been set for this actor!!!"));
	}

	// Checks the array in GameInstance whether the crystal should exist or not (has it already been picked up)
	if (!GameInstance->ExistingCrystals.Contains(CrystalID))
	{
		this->Destroy();
	}
	
	InteractableData = InstanceInteractableData;
}

// Called every frame
void ACrystalCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrystalCollectible::Interact()
{
	GameInstance->ExistingCrystals.Remove(CrystalID);
	GameInstance->Score++;
	GameInstance->OnScoreUpdated.Broadcast();
	UGameplayStatics::PlaySound2D(GetWorld(), PickupSound);

	this->Destroy();
}