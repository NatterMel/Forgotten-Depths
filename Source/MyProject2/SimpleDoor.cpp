// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleDoor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interactable.h"
#include "GameFramework/Character.h"

// Sets default values
ASimpleDoor::ASimpleDoor()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(RootComponent);

    bIsOpen = true;

}

// Called when the game starts or when spawned
void ASimpleDoor::BeginPlay()
{
    Super::BeginPlay();

}

void ASimpleDoor::Tick(float DeltaTime)
{
    if (bIsmoving && DoorMesh)
    {
        FVector Current = DoorMesh->GetRelativeLocation();
        FVector New = FMath::VInterpTo(Current, TargetLocation, DeltaTime, DoorOpenSpeed);

        DoorMesh->SetRelativeLocation(New);

        if (FVector::Dist(New, TargetLocation) < 0.5f)
        {    
            DoorMesh->SetRelativeLocation(TargetLocation);
            bIsmoving = false;
        }
    }
}
void ASimpleDoor::OnInteract_Implementation()
{
    Execute_Open(this);
}

void ASimpleDoor::Open_Implementation()
{
    if (bHasBeenOpened) return;

    FVector NewLocation = bIsOpen ? OpenRelativePosition : FVector::ZeroVector;
    TargetLocation = NewLocation;
    bIsmoving = true;
    bIsOpen = false;
    bHasBeenOpened = true;
}

