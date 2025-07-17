#include "LevelTrigger.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "MySaveGame.h"
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
    if (OtherActor && OtherActor->IsA(AMainCharacter::StaticClass()))
    {

        if (LevelToLoad.ToSoftObjectPath().IsValid())
        {      
            SaveLevelProgress();
            FString LevelPath = LevelToLoad.ToSoftObjectPath().GetLongPackageName();
            UGameplayStatics::OpenLevel(this, FName(*LevelPath));

        }
    }
}

void ALevelTrigger::SaveLevelProgress()
{
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    SaveGameInstance->PlayerLevel = indexToLoad;
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySaveSlot"), 0);
}

