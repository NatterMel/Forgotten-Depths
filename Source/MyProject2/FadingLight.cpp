// Fill out your copyright notice in the Description page of Project Settings.


#include "FadingLight.h"
#include "Components/PointLightComponent.h"

AFadingLight::AFadingLight()
{
    PrimaryActorTick.bCanEverTick = true;

    PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    RootComponent = PointLight;
}

void AFadingLight::BeginPlay()
{
    Super::BeginPlay();

    CurrentIntensity = FMath::FRandRange(MinStartIntensity, MaxStartIntensity);
    PointLight->SetIntensity(CurrentIntensity);
}

void AFadingLight::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentIntensity > 0.0f)
    {
        CurrentIntensity -= FadeRate * DeltaTime;
        if (CurrentIntensity <= 0.0f)
        {
            Destroy();
        }
        else
        {
            PointLight->SetIntensity(CurrentIntensity);
        }
    }
}

