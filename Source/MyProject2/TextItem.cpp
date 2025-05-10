// Fill out your copyright notice in the Description page of Project Settings.


#include "TextItem.h"
#include "MyWidgetitem.h"
#include "Kismet/GameplayStatics.h"
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

    if (!PreviewSceneActor && PreviewSceneClass)
    {
        PreviewSceneActor = GetWorld()->SpawnActor<AMyPreviewScene>(PreviewSceneClass);
        if (PreviewSceneActor)
        {
            PreviewSceneActor->SetActorLocation(FVector(100000.f, 0.f, 0.f));
            PreviewSceneActor->SceneCapture->TextureTarget = RenderTarget;
            PreviewSceneActor->SetPreviewMesh(MeshComponent);
        }
    }


    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    UMyWidgetitem* Widget = CreateWidget<UMyWidgetitem>(PC, ItemInfoWidgetClass);
    if (Widget)
    {
        Widget->DisplayedText = ItemDescription;
        Widget->AddToViewport();
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
        UGameplayStatics::SetGamePaused(GetWorld(), true);
    }
}
