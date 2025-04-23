// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Openable.h"
#include "Interactable.h"
#include "ProximityComponent.h"
#include "LeverActor.generated.h"

UCLASS()
class MYPROJECT2_API ALeverActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALeverActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeverMesh;

	UPROPERTY(VisibleAnywhere)
	UProximityComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = "Lever")
	AActor* ActorToActivate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation() override;

};
