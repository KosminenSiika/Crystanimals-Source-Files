// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "CrystalCollectible.generated.h"

// Forward Declarations
class UTreasureGameInstance;

UCLASS()
class CRYSTANIMALS_API ACrystalCollectible : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystalCollectible();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Crystal")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Crystal")
	FInteractableData InstanceInteractableData;

	UPROPERTY(EditInstanceOnly, Category = "Crystal")
	FString CrystalID;

	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	virtual void Interact() override;
	

};
