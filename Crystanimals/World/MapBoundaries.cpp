// Fill out your copyright notice in the Description page of Project Settings.


#include "MapBoundaries.h"
#include "Components/BoxComponent.h"
#include "UserInterface/AnimalHUD.h"
#include "Player/AnimalCharacter.h"

// Sets default values
AMapBoundaries::AMapBoundaries()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a collision volume for the actor
	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionVolume"));
	CollisionVolume->SetupAttachment(RootComponent);
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AMapBoundaries::BeginOverlap);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AMapBoundaries::EndOverlap);
}

// Called when the game starts or when spawned
void AMapBoundaries::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AAnimalHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

// Called every frame
void AMapBoundaries::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapBoundaries::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HUD)
	{
		HUD->HideOutOfBoundsWidget();
	}
}

void AMapBoundaries::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HUD)
	{
		if (OtherComp == GetWorld()->GetFirstPlayerController()->GetPawn()->GetRootComponent())
		{
			HUD->DisplayOutOfBoundsWidget();
		}
	}
}

