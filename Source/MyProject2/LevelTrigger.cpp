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
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    TriggerBox->SetGenerateOverlapEvents(true);
}

void ALevelTrigger::BeginPlay()
{
    Super::BeginPlay();

    // Bind overlap event
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelTrigger::OnOverlapBegin);
}

void ALevelTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
    {
        if (LevelToLoad.IsValid())
        {
            FString LevelPath = LevelToLoad.GetAssetName();  
            UGameplayStatics::OpenLevel(this, FName(*LevelPath));
        }
    }
}

