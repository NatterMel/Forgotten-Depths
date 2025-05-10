// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProximityComponent.h"
#include "Interactable.h"
#include "Engine/TextureRenderTarget2D.h"
#include "MyPreviewScene.h"
#include "TextItem.generated.h"

UCLASS()
class MYPROJECT2_API ATextItem : public AActor, public IInteractable
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemDescription;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere)
	UProximityComponent* Trigger;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<AMyPreviewScene> PreviewSceneClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTextureRenderTarget2D* RenderTarget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ItemInfoWidgetClass;

	AMyPreviewScene* PreviewSceneActor;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation() override;
	ATextItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void ShowItemInfoUI();

};
