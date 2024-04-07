// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MapBoundaries.generated.h"

UCLASS()
class CRYSTANIMALS_API AMapBoundaries : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapBoundaries();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult &SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<UShapeComponent> CollisionVolume;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	

};
