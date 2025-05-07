// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProximityComponent.h"
#include "Interactable.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "TextItem.generated.h"

UCLASS()
class MYPROJECT2_API ATextItem : public AActor, public IInteractable
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemDescription;

	UPROPERTY(VisibleAnywhere)
	UProximityComponent* Trigger;

	UPROPERTY(VisibleAnywhere)
	class USceneCaptureComponent2D* Capture;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation() override;
	ATextItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void ShowItemInfoUI();
};
