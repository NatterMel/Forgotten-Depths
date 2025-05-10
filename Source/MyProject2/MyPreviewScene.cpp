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
    MeshComponent->SetRelativeLocation(FVector(0, 0, -5));
    MeshComponent->SetMobility(EComponentMobility::Movable);

    SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
    SceneCapture->SetupAttachment(RootComponent);
    SceneCapture->SetRelativeLocation(FVector(200.f, 0.f, 0.f)); // In front of mesh
    SceneCapture->bCaptureEveryFrame = true;
    SceneCapture->bCaptureOnMovement = false;

    PreviewLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PreviewLight"));
    PreviewLight->SetupAttachment(RootComponent);
    PreviewLight->SetIntensity(5000.0f); // Adjust as needed
    PreviewLight->SetLightColor(FLinearColor::White);
    PreviewLight->SetRelativeLocation(FVector(0.f, 0.f, 0.f)); // Offset to shine on mesh
    PreviewLight->bUseInverseSquaredFalloff = false; // Optional: Use linear falloff
    PreviewLight->AttenuationRadius = 1000.f; // Controls how far light reaches
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

