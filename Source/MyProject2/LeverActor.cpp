// Fill out your copyright notice in the Description page of Project Settings.
#include "LeverActor.h"
#include "Openable.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ALeverActor::ALeverActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverMesh"));
	LeverMesh->SetupAttachment(RootComponent);

	Trigger = CreateDefaultSubobject<UProximityComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALeverActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALeverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALeverActor::OnInteract_Implementation()
{
	if (ActorToActivate)
	{
		bool bOn = UKismetSystemLibrary::DoesImplementInterface(ActorToActivate, UOpenable::StaticClass());
		if (bOn)
		{
			IOpenable::Execute_Open(ActorToActivate);
		}
	}
}


