// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "ProgressionShop.generated.h"

// Forward Declarations
class UTreasureGameInstance;

UCLASS()
class CRYSTANIMALS_API AProgressionShop : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProgressionShop();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> CrystalBatch1 = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> CrystalBatch2 = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> CrystalBatch3 = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> CrystalBatch4 = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> CrystalBatch5 = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> CrystalBatch6 = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> CrystalBatch7 = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Shop")
	TObjectPtr<UStaticMeshComponent> CrystalBatch8 = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "Shop")
	FInteractableData InstanceInteractableData;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> UnlocksClaimSound = nullptr;

	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UFUNCTION()
	void UpdatePlinthCrystals();

	UFUNCTION()
	void SetBatchIsPlaced(UStaticMeshComponent* CrystalBatch, bool NewIsPlaced);

	virtual void Interact() override;

};
