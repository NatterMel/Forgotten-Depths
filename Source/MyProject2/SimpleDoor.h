// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Interactable.h"
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

public:	
	virtual void OnInteract_Implementation(AActor* Interactor) override;

protected:

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* DoorMesh;

    bool bIsOpen;
};

