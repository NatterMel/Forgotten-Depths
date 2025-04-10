// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleDoor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interactable.h"
#include "GameFramework/Character.h"

// Sets default values
ASimpleDoor::ASimpleDoor()
{
    PrimaryActorTick.bCanEverTick = false;

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;


    bIsOpen = false;

}

// Called when the game starts or when spawned
void ASimpleDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASimpleDoor::OnInteract_Implementation(AActor* Interactor)
{
    bIsOpen = !bIsOpen;
    FRotator NewRotation = bIsOpen ? FRotator(0.f, 90.f, 0.f) : FRotator(0.f, 0.f, 0.f);
    DoorMesh->SetRelativeRotation(NewRotation);
}

