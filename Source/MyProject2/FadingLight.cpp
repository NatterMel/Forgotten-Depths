// Fill out your copyright notice in the Description page of Project Settings.


#include "FadingLight.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
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
}

void AFadingLight::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (CurrentIntensity > 0.0f)
    {
        CurrentIntensity -= FadeRate * DeltaTime;
        if (CurrentIntensity <= 0.1f)
        {
            APawn* PlayerPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
            if (AMainCharacter* MyCharacter = Cast<AMainCharacter>(PlayerPawn))
            {
                MyCharacter->RemoveLights();
                Destroy();
            };

        }
        else
        {
            PointLight->SetIntensity(CurrentIntensity);
            CurrentIntensity = PointLight->Intensity;
        }
    }
}

void AFadingLight::SetStartIntensity(float intensity, float rate)
{
    CurrentIntensity = intensity;
    PointLight->SetIntensity(CurrentIntensity);
    FadeRate = rate;
}

void AFadingLight::SetColor(const FLinearColor& NewColor)
{
    if (PointLight)
    {
        PointLight->SetLightColor(NewColor);
    }
}

