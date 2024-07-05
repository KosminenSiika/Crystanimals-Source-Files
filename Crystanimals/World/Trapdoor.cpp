// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Trapdoor.h"
#include "Core/TreasureGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATrapdoor::ATrapdoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>("FrameMesh");
	SetRootComponent(FrameMesh);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	DoorMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATrapdoor::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("Trapdoor unable to get reference to GameInstance"));

	InteractableData = InstanceInteractableData;

	if (GameInstance->bIsTrapdoorOpen)
	{
		OpenTrapdoor();
	}
}

void ATrapdoor::OpenTrapdoor()
{
	DoorMesh->SetRelativeRotation(FRotator(0, 0, -100));
	InteractableData.Action = FText::FromString("close");
	GameInstance->bIsTrapdoorOpen = true;
}

void ATrapdoor::CloseTrapdoor()
{
	DoorMesh->SetRelativeRotation(FRotator::ZeroRotator);
	InteractableData.Action = FText::FromString("open");
	GameInstance->bIsTrapdoorOpen = false;
}

void ATrapdoor::Interact()
{
	if (GameInstance->bHasKey)
	{
		if (GameInstance->bIsTrapdoorOpen)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), TrapdoorCloseSound, GetActorLocation());
			CloseTrapdoor();
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), TrapdoorOpenSound, GetActorLocation());
			OpenTrapdoor();
			// "Unlocked with mysterious key" notification widget
		}
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), TrapdoorLockedSound, GetActorLocation());
		// "It's locked" notification widget
		UE_LOG(LogTemp, Warning, TEXT("It's locked!"));
	}
}
