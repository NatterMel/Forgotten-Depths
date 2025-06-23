#include "LevelTrigger.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

ALevelTrigger::ALevelTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    // Enable collision to trigger overlap events
    TriggerBox->InitBoxExtent(FVector(200.f));
    TriggerBox->SetCollisionProfileName("Trigger");
    TriggerBox->SetGenerateOverlapEvents(true);

    TriggerBox->bHiddenInGame = false;
    TriggerBox->SetVisibility(true);
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelTrigger::OnOverlapBegin);
}

void ALevelTrigger::BeginPlay()
{
    Super::BeginPlay();

}

void ALevelTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Overlap triggered!"));
    }

    if (OtherActor && OtherActor->IsA(AMainCharacter::StaticClass()))
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlapping MainCharacter"));

        if (LevelToLoad.ToSoftObjectPath().IsValid())
        {
            FString LevelPath = LevelToLoad.GetAssetName();
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Loading Level: %s"), *LevelPath));

            UGameplayStatics::OpenLevel(this, FName(*LevelPath));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LevelToLoad is not valid!"));
        }
    }
}

