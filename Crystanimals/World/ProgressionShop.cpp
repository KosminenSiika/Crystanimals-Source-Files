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

	CrystalBatch1 = CreateDefaultSubobject<UStaticMeshComponent>("CrystalBatch1");
	CrystalBatch1->SetupAttachment(Mesh);

	CrystalBatch2 = CreateDefaultSubobject<UStaticMeshComponent>("CrystalBatch2");
	CrystalBatch2->SetupAttachment(Mesh);

	CrystalBatch3 = CreateDefaultSubobject<UStaticMeshComponent>("CrystalBatch3");
	CrystalBatch3->SetupAttachment(Mesh);

	CrystalBatch4 = CreateDefaultSubobject<UStaticMeshComponent>("CrystalBatch4");
	CrystalBatch4->SetupAttachment(Mesh);

	CrystalBatch5 = CreateDefaultSubobject<UStaticMeshComponent>("CrystalBatch5");
	CrystalBatch5->SetupAttachment(Mesh);

	CrystalBatch6 = CreateDefaultSubobject<UStaticMeshComponent>("CrystalBatch6");
	CrystalBatch6->SetupAttachment(Mesh);

	CrystalBatch7 = CreateDefaultSubobject<UStaticMeshComponent>("CrystalBatch7");
	CrystalBatch7->SetupAttachment(Mesh);

	CrystalBatch8 = CreateDefaultSubobject<UStaticMeshComponent>("CrystalBatch8");
	CrystalBatch8->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AProgressionShop::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<UTreasureGameInstance>();
	checkf(GameInstance, TEXT("ProgressionShop unable to get reference to GameInstance"));

	InteractableData = InstanceInteractableData;

	UpdatePlinthCrystals();
}

// Called every frame
void AProgressionShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("CrystalBatch8 collision is %s, Type: %d"), CrystalBatch8->IsCollisionEnabled() ? TEXT("enabled") : TEXT("disabled"), CrystalBatch8->GetCollisionEnabled());

}

void AProgressionShop::UpdatePlinthCrystals()
{
	if (GameInstance->Score >= 80)
	{
		if (!GameInstance->bNewUnlocksNotClaimed)
		{
			SetBatchIsPlaced(CrystalBatch8, true);
		} 
		else
		{
			SetBatchIsPlaced(CrystalBatch8, false);
		}
		SetBatchIsPlaced(CrystalBatch7, true);
		SetBatchIsPlaced(CrystalBatch6, true);
		SetBatchIsPlaced(CrystalBatch5, true);
		SetBatchIsPlaced(CrystalBatch4, true);
		SetBatchIsPlaced(CrystalBatch3, true);
		SetBatchIsPlaced(CrystalBatch2, true);
		SetBatchIsPlaced(CrystalBatch1, true);
	}
	else if (GameInstance->Score >= 70)
	{
		SetBatchIsPlaced(CrystalBatch8, false);
		if (!GameInstance->bNewUnlocksNotClaimed)
		{
			SetBatchIsPlaced(CrystalBatch7, true);
		}
		else
		{
			SetBatchIsPlaced(CrystalBatch7, false);
		}
		SetBatchIsPlaced(CrystalBatch6, true);
		SetBatchIsPlaced(CrystalBatch5, true);
		SetBatchIsPlaced(CrystalBatch4, true);
		SetBatchIsPlaced(CrystalBatch3, true);
		SetBatchIsPlaced(CrystalBatch2, true);
		SetBatchIsPlaced(CrystalBatch1, true);
	}
	else if (GameInstance->Score >= 60)
	{
		SetBatchIsPlaced(CrystalBatch8, false);
		SetBatchIsPlaced(CrystalBatch7, false);
		if (!GameInstance->bNewUnlocksNotClaimed)
		{
			SetBatchIsPlaced(CrystalBatch6, true);
		}
		else
		{
			SetBatchIsPlaced(CrystalBatch6, false);
		}
		SetBatchIsPlaced(CrystalBatch5, true);
		SetBatchIsPlaced(CrystalBatch4, true);
		SetBatchIsPlaced(CrystalBatch3, true);
		SetBatchIsPlaced(CrystalBatch2, true);
		SetBatchIsPlaced(CrystalBatch1, true);
	}
	else if (GameInstance->Score >= 50)
	{
		SetBatchIsPlaced(CrystalBatch8, false);
		SetBatchIsPlaced(CrystalBatch7, false);
		SetBatchIsPlaced(CrystalBatch6, false);
		if (!GameInstance->bNewUnlocksNotClaimed)
		{
			SetBatchIsPlaced(CrystalBatch5, true);
		}
		else
		{
			SetBatchIsPlaced(CrystalBatch5, false);
		}
		SetBatchIsPlaced(CrystalBatch4, true);
		SetBatchIsPlaced(CrystalBatch3, true);
		SetBatchIsPlaced(CrystalBatch2, true);
		SetBatchIsPlaced(CrystalBatch1, true);
	}
	else if (GameInstance->Score >= 40)
	{
		SetBatchIsPlaced(CrystalBatch8, false);
		SetBatchIsPlaced(CrystalBatch7, false);
		SetBatchIsPlaced(CrystalBatch6, false);
		SetBatchIsPlaced(CrystalBatch5, false);
		if (!GameInstance->bNewUnlocksNotClaimed)
		{
			SetBatchIsPlaced(CrystalBatch4, true);
		}
		else
		{
			SetBatchIsPlaced(CrystalBatch4, false);
		}
		SetBatchIsPlaced(CrystalBatch3, true);
		SetBatchIsPlaced(CrystalBatch2, true);
		SetBatchIsPlaced(CrystalBatch1, true);
	}
	else if (GameInstance->Score >= 30)
	{
		SetBatchIsPlaced(CrystalBatch8, false);
		SetBatchIsPlaced(CrystalBatch7, false);
		SetBatchIsPlaced(CrystalBatch6, false);
		SetBatchIsPlaced(CrystalBatch5, false);
		SetBatchIsPlaced(CrystalBatch4, false);
		if (!GameInstance->bNewUnlocksNotClaimed)
		{
			SetBatchIsPlaced(CrystalBatch3, true);
		}
		else
		{
			SetBatchIsPlaced(CrystalBatch3, false);
		}
		SetBatchIsPlaced(CrystalBatch2, true);
		SetBatchIsPlaced(CrystalBatch1, true);
	}
	else if (GameInstance->Score >= 20)
	{
		SetBatchIsPlaced(CrystalBatch8, false);
		SetBatchIsPlaced(CrystalBatch7, false);
		SetBatchIsPlaced(CrystalBatch6, false);
		SetBatchIsPlaced(CrystalBatch5, false);
		SetBatchIsPlaced(CrystalBatch4, false);
		SetBatchIsPlaced(CrystalBatch3, false);
		if (!GameInstance->bNewUnlocksNotClaimed)
		{
			SetBatchIsPlaced(CrystalBatch2, true);
		}
		else
		{
			SetBatchIsPlaced(CrystalBatch2, false);
		}
		SetBatchIsPlaced(CrystalBatch1, true);
	}
	else if (GameInstance->Score >= 10)
	{
		SetBatchIsPlaced(CrystalBatch8, false);
		SetBatchIsPlaced(CrystalBatch7, false);
		SetBatchIsPlaced(CrystalBatch6, false);
		SetBatchIsPlaced(CrystalBatch5, false);
		SetBatchIsPlaced(CrystalBatch4, false);
		SetBatchIsPlaced(CrystalBatch3, false);
		SetBatchIsPlaced(CrystalBatch2, false);
		if (!GameInstance->bNewUnlocksNotClaimed)
		{
			SetBatchIsPlaced(CrystalBatch1, true);
		}
		else
		{
			SetBatchIsPlaced(CrystalBatch1, false);
		}
	}
	else
	{
		SetBatchIsPlaced(CrystalBatch8, false);
		SetBatchIsPlaced(CrystalBatch7, false);
		SetBatchIsPlaced(CrystalBatch6, false);
		SetBatchIsPlaced(CrystalBatch5, false);
		SetBatchIsPlaced(CrystalBatch4, false);
		SetBatchIsPlaced(CrystalBatch3, false);
		SetBatchIsPlaced(CrystalBatch2, false);
		SetBatchIsPlaced(CrystalBatch1, false);
	}
}

void AProgressionShop::SetBatchIsPlaced(UStaticMeshComponent* CrystalBatch, bool NewIsPlaced)
{
	if (NewIsPlaced)
	{
		CrystalBatch->SetHiddenInGame(false, true);
		CrystalBatch->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		
		TArray<USceneComponent*> BatchChildren = CrystalBatch->GetAttachChildren();
		for (USceneComponent* Child : BatchChildren)
		{
			UStaticMeshComponent* CastedChild = Cast<UStaticMeshComponent>(Child);
			CastedChild->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
	else
	{
		CrystalBatch->SetHiddenInGame(true, true);
		CrystalBatch->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		TArray<USceneComponent*> BatchChildren = CrystalBatch->GetAttachChildren();
		for (USceneComponent* Child : BatchChildren)
		{
			UStaticMeshComponent* CastedChild = Cast<UStaticMeshComponent>(Child);
			CastedChild->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void AProgressionShop::Interact()
{
	UGameplayStatics::PlaySound2D(GetWorld(), UnlocksClaimSound);
	GameInstance->bNewUnlocksNotClaimed = false;
	UpdatePlinthCrystals();
	GameInstance->OnUnlocksClaimed.Broadcast();
	GameInstance->SaveGame();
}

