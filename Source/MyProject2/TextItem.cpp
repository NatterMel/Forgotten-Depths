// Fill out your copyright notice in the Description page of Project Settings.


#include "TextItem.h"

// Sets default values
ATextItem::ATextItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetRelativeLocation(FVector(0, 0, 0));
	MeshComponent->SetMobility(EComponentMobility::Movable);

	Trigger = CreateDefaultSubobject<UProximityComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	Capture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	Capture->SetupAttachment(RootComponent);
	Capture->SetRelativeLocation(FVector(200.f, 0.f, 0.f)); // In front of mesh
	Capture->bCaptureEveryFrame = true;
	Capture->bCaptureOnMovement = false;
}



// Called when the game starts or when spawned
void ATextItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATextItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATextItem::OnInteract_Implementation()
{
	ShowItemInfoUI();
}

void ATextItem::ShowItemInfoUI()
{
}