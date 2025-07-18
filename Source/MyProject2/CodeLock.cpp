// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeLock.h"
#include "Openable.h"
#include "Kismet/GameplayStatics.h"
#include "CodeLockWidget.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
ACodeLock::ACodeLock()
{
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
void ACodeLock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACodeLock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACodeLock::EnterDigit(int32 Digit)
{
    if (EnteredCode.Num() >= 4)
    {
        ResetInput();
    }

    EnteredCode.Add(Digit);
}

void ACodeLock::ResetInput()
{
    EnteredCode.Empty();
}

void ACodeLock::OnCodeCorrect()
{
    if (ActiveWidget)
    {
        ActiveWidget->CloseWidget();
        ActiveWidget = nullptr;
    }
    if (ActorToActivate)
    {
        bool bOn = UKismetSystemLibrary::DoesImplementInterface(ActorToActivate, UOpenable::StaticClass());
        if (bOn)
        {
            IOpenable::Execute_Open(ActorToActivate);
            bCanBeInteractedWith = false;
        }
    }
}

void ACodeLock::OnInteract_Implementation()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    UCodeLockWidget* Widget = CreateWidget<UCodeLockWidget>(PC, ItemInfoWidgetClass);
    if (Widget)
    {
        ActiveWidget = Widget;
        Widget->CodeLockRef = this;
        Widget->AddToViewport();
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
    }
}


void ACodeLock::CheckCode()
{
    FString EnteredString;
    for (int32 Digit : EnteredCode)
    {
        EnteredString += FString::FromInt(Digit);
    }

    FString CorrectString;
    for (int32 Digit : CorrectCode)
    {
        CorrectString += FString::FromInt(Digit);
    }

    // Print to screen
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Entered Code: %s"), *EnteredString));
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Correct Code: %s"), *CorrectString));
    }

    // Print to output log
    UE_LOG(LogTemp, Warning, TEXT("Entered Code: %s"), *EnteredString);
    UE_LOG(LogTemp, Warning, TEXT("Correct Code: %s"), *CorrectString);

    // Check logic
    if (EnteredCode == CorrectCode)
    {
        OnCodeCorrect();
    }
    else
    {
        ResetInput();
    }
}
