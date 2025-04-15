// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Interactable.h"
#include "ProximityComponent.h"
#include "SimpleDoor.generated.h"

UCLASS()
class MYPROJECT2_API ASimpleDoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	virtual void OnInteract_Implementation() override;

	UPROPERTY(EditDefaultsOnly)
	FVector OpenRelativePosition;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = 200.f;

protected:

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere)
	UProximityComponent* Trigger;

    bool bIsOpen;
	bool bIsmoving;

	FVector TargetLocation;
};

