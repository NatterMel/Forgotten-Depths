// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "LightStatue.generated.h"

UCLASS()
class MYPROJECT2_API ALightStatue : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightStatue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    int32 CurrentColorIndex = 0;
    float TimeAccumulator = 0.0f;
    bool bSequenceFinished = false;

    void UpdateLights();
    void TurnOffLights();
    void RestartSequence();
    FTimerHandle RestartTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    USceneComponent* Root;

    // Two point lights
    UPROPERTY(VisibleAnywhere)
    UPointLightComponent* Light1;

    UPROPERTY(VisibleAnywhere)
    UPointLightComponent* Light2;

    // Color sequence editable in editor
    UPROPERTY(EditAnywhere, Category = "Color Sequence")
    TArray<FLinearColor> ColorSequence;

    // Time between color changes
    UPROPERTY(EditAnywhere, Category = "Color Sequence")
    float ColorChangeInterval = 1.0f;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* MeshComponent;

};
