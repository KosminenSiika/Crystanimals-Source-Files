// Fill out your copyright notice in the Description page of Project Settings.


#include "World/CrystalCollectible.h"

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
	
	InteractableData = InstanceInteractableData;
}

// Called every frame
void ACrystalCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrystalCollectible::Interact()
{
	// TODO: REPLACE THIS WITH ACTUAL FUNCTIONALITY (DISABLE COLLISION, MAKE INVISIBLE, UPDATE SCORE, SAVE GAME)
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact override on CrystalCollectible"));

}