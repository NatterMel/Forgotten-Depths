#include "MyPreviewScene.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SceneCaptureComponent2D.h"

// Sets default values
AMyPreviewScene::AMyPreviewScene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetRelativeLocation(FVector(0, 0, 0));
    MeshComponent->SetMobility(EComponentMobility::Movable);

    SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
    SceneCapture->SetupAttachment(RootComponent);
    SceneCapture->SetRelativeLocation(FVector(200.f, 0.f, 0.f)); // In front of mesh
    SceneCapture->bCaptureEveryFrame = true;
    SceneCapture->bCaptureOnMovement = false;

}

void AMyPreviewScene::SetPreviewMesh(UStaticMeshComponent* InMesh)
{
    UStaticMesh* StaticMesh = InMesh->GetStaticMesh();
    MeshComponent->SetStaticMesh(StaticMesh);
}

// Called when the game starts or when spawned
void AMyPreviewScene::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPreviewScene::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

