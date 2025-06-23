// Fill out your copyright notice in the Description page of Project Settings.


#include "LightStatue.h"

// Sets default values
ALightStatue::ALightStatue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    Light1 = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light1"));
    Light1->SetupAttachment(Root);
    Light1->SetRelativeLocation(FVector(-50.f, 0.f, 0.f));
    Light1->SetIntensity(5000.f);

    Light2 = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light2"));
    Light2->SetupAttachment(Root);
    Light2->SetRelativeLocation(FVector(50.f, 0.f, 0.f));
    Light2->SetIntensity(5000.f);

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetRelativeLocation(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void ALightStatue::BeginPlay()
{
	Super::BeginPlay();
    UpdateLights();
}

void ALightStatue::UpdateLights()
{
    if (ColorSequence.IsValidIndex(CurrentColorIndex))
    {
        FLinearColor CurrentColor = ColorSequence[CurrentColorIndex];
        Light1->SetLightColor(CurrentColor);
        Light2->SetLightColor(CurrentColor);
    }
}

void ALightStatue::TurnOffLights()
{
    Light1->SetVisibility(false);
    Light2->SetVisibility(false);
}

void ALightStatue::RestartSequence()
{
    Light1->SetVisibility(true);
    Light2->SetVisibility(true);
    CurrentColorIndex = 0;
    TimeAccumulator = 0.0f;
    bSequenceFinished = false;
    UpdateLights();
}

// Called every frame
void ALightStatue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bSequenceFinished || ColorSequence.Num() == 0)
        return;

    TimeAccumulator += DeltaTime;
    if (TimeAccumulator >= ColorChangeInterval)
    {
        TimeAccumulator = 0.0f;

        UpdateLights();

        CurrentColorIndex++;

        if (CurrentColorIndex >= ColorSequence.Num())
        {
            bSequenceFinished = true;
            GetWorldTimerManager().SetTimerForNextTick(this, &ALightStatue::TurnOffLights);

            GetWorldTimerManager().SetTimer(
                RestartTimerHandle,
                this,
                &ALightStatue::RestartSequence,
                ColorChangeInterval * 2.0f,
                false
            );
        }
    }
}

