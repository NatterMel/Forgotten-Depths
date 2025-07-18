// Fill out your copyright notice in the Description page of Project Settings.
#include "ProximityComponent.h"
#include "MainCharacter.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UProximityComponent::UProximityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector(200.f));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetGenerateOverlapEvents(true);
	BoxComponent->SetupAttachment(this);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UProximityComponent::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &UProximityComponent::OnOverlapEnd);
}


// Called when the game starts
void UProximityComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (!Owner) return;

	USceneComponent* Root = Owner->GetRootComponent();
	if (!Root) return;

	if (BoxComponent)
	{
		BoxComponent->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

void UProximityComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !Owner) return;

	
	FProperty* BoolProperty = Owner->GetClass()->FindPropertyByName("bCanBeInteractedWith");
	if (FBoolProperty* BoolProp = CastField<FBoolProperty>(BoolProperty))
	{
		bool bValue = BoolProp->GetPropertyValue_InContainer(Owner);
		if (!bValue) return;
	}

	if (AMainCharacter* Actor = Cast<AMainCharacter>(OtherActor))
	{
		Actor->AddInteract(Owner);
	}
}
void UProximityComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor) 
	{
		if (AMainCharacter* Actor = Cast<AMainCharacter>(OtherActor))
		{
			Actor->RemoveInteract();
		}
	}

}

