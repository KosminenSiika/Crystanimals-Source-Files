// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "LevelPortal.generated.h"

UCLASS()
class CRYSTANIMALS_API ALevelPortal : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelPortal();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Portal")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditInstanceOnly, Category = "Portal")
	FInteractableData InstanceInteractableData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	virtual void Interact() override;

};
