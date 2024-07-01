// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "Trapdoor.generated.h"

// Forward Declarations
class UTreasureGameInstance;

UCLASS()
class CRYSTANIMALS_API ATrapdoor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrapdoor();

protected:
	UPROPERTY(EditAnywhere, Category = "Trapdoor")
	TObjectPtr<UStaticMeshComponent> FrameMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Trapdoor")
	TObjectPtr<UStaticMeshComponent> DoorMesh = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "Trapdoor")
	FInteractableData InstanceInteractableData;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UTreasureGameInstance> GameInstance = nullptr;

	UFUNCTION()
	void OpenTrapdoor();

	UFUNCTION()
	void CloseTrapdoor();

	virtual void Interact() override;

};
