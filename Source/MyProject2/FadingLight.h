// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FadingLight.generated.h"

UCLASS()
class MYPROJECT2_API AFadingLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFadingLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* PointLight;

	float FadeRate;
	
	float CurrentIntensity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStartIntensity(float intensity, float rate);

};
