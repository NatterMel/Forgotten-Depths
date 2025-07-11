// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "Openable.h"
#include "LightStatue.generated.h"

UENUM(BlueprintType)
enum class ELightStatueMode : uint8
{
    Automatic     UMETA(DisplayName = "Automatic"),
    Manual        UMETA(DisplayName = "Manual")
};
UCLASS()
class MYPROJECT2_API ALightStatue : public AActor, public IOpenable
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


    UFUNCTION(BlueprintCallable, Category = "Light Statue")
    void UpdateLights();

    UFUNCTION(BlueprintCallable, Category = "Light Statue")
    void TurnOffLights();

    UFUNCTION(BlueprintCallable, Category = "Light Statue")
    void RestartSequence();
    FTimerHandle RestartTimerHandle;

    UFUNCTION(BlueprintCallable, Category = "Light Statue")
    void AdvanceToNextColor();

public:	

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light Statue")
    ELightStatueMode LightStatueMode = ELightStatueMode::Automatic;
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

    virtual void Open_Implementation() override;

};
