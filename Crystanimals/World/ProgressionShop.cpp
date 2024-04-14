// Fill out your copyright notice in the Description page of Project Settings.


#include "World/ProgressionShop.h"

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
	
}

// Called every frame
void AProgressionShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProgressionShop::Interact()
{
	// TODO: REPLACE THIS WITH ACTUAL FUNCTIONALITY (ENABLE NEW FEATURES BASED ON PROGRESSION)
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact override on ProgressionShop"));

}

