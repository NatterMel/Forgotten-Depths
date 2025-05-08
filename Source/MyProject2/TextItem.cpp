// Fill out your copyright notice in the Description page of Project Settings.


#include "TextItem.h"
#include "MyWidgetitem.h"
#include "MyPreviewScene.h"

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
    if (!RenderTarget || !ItemInfoWidgetClass || !MeshComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("ATextItem: Missing required asset."));
        return;
    }

    if (!PreviewSceneActor)
    {
        PreviewSceneActor = GetWorld()->SpawnActor<AMyPreviewScene>(AMyPreviewScene::StaticClass());
        PreviewSceneActor->SetActorHiddenInGame(true);
        PreviewSceneActor->SceneCapture->TextureTarget = RenderTarget;
    }

    PreviewSceneActor->SetPreviewMesh(MeshComponent);

    UMyWidgetitem* Widget = CreateWidget<UMyWidgetitem>(GetWorld(), ItemInfoWidgetClass);
    if (Widget)
    {
        Widget->DisplayedText = ItemDescription;
        Widget->AddToViewport();
    }
}
