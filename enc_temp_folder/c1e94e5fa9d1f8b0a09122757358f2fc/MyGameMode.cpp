// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameMode.h"

#include "Kismet/GameplayStatics.h"

void AMyGameMode::HandleRedColor()
{
    SelectedColor = EColorType::Red;
    SetObjectsVisibility(SelectedColor);
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Selected Color: Red"));
}

void AMyGameMode::HandleGreenColor()
{
    SelectedColor = EColorType::Green;
    SetObjectsVisibility(SelectedColor);
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Selected Color: Green"));
}

void AMyGameMode::HandleBlueColor()
{
    SelectedColor = EColorType::Blue;
    SetObjectsVisibility(SelectedColor);
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Selected Color: Blue"));
}

void AMyGameMode::HandleWhiteColor()
{
    SelectedColor = EColorType::White;
    SetObjectsVisibility(SelectedColor);
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, TEXT("Selected Color: White"));
}

void AMyGameMode::SetObjectsVisibility(EColorType Color)
{
    HideAll();
    TArray<AActor*>* VisibleGroup = nullptr;
    switch (SelectedColor)
    {
    case EColorType::Red:    VisibleGroup = &RedActors;    break;
    case EColorType::Green:  VisibleGroup = &GreenActors;  break;
    case EColorType::Blue:   VisibleGroup = &BlueActors;   break;
    case EColorType::White: VisibleGroup = &WhiteActors; break;
    }

    if (VisibleGroup)
    {
        for (AActor* Actor : *VisibleGroup)
        {
            if (Actor)
            {
                Actor->SetActorHiddenInGame(false);
                Actor->SetActorEnableCollision(true);
                Actor->SetActorTickEnabled(true);
            }
        }
    }
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "RedOnly", RedActors);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "GreenOnly", GreenActors);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "BlueOnly", BlueActors);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "YellowOnly", WhiteActors);
    PrintActorList("RedOnly", RedActors);
    PrintActorList("GreenOnly", GreenActors);
    PrintActorList("BlueOnly", BlueActors);
    PrintActorList("YellowOnly", WhiteActors);
    HideAll();
}

void AMyGameMode::HideAll()
{
    auto HideAll = [](const TArray<AActor*>& Actors)
        {
            for (AActor* Actor : Actors)
            {
                if (Actor)
                {
                    Actor->SetActorHiddenInGame(true);
                    Actor->SetActorEnableCollision(false);
                    Actor->SetActorTickEnabled(false);
                }
            }
        };
    HideAll(RedActors);
    HideAll(GreenActors);
    HideAll(BlueActors);
    HideAll(WhiteActors);
}
void AMyGameMode::PrintActorList(const FString& TagName, const TArray<AActor*>& ActorArray)
{
    FString ActorNames = FString::Printf(TEXT("Actors with Tag %s:"), *TagName);
    for (AActor* Actor : ActorArray)
    {
        if (Actor)
        {
            ActorNames += FString::Printf(TEXT(" %s,"), *Actor->GetName());
        }
    }

    // Display the actor names on the screen (top-left corner)
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, ActorNames);
}
