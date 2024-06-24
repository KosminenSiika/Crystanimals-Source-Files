// Fill out your copyright notice in the Description page of Project Settings.


#include "World/BlueIce.h"

// Sets default values
ABlueIce::ABlueIce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlueIce::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlueIce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

