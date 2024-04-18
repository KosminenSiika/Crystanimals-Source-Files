// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "ProgressionShop.generated.h"

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

	UPROPERTY(EditInstanceOnly, Category = "Shop")
	FInteractableData InstanceInteractableData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	virtual void Interact() override;

};
