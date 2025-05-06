// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EColorType : uint8
{
	Red     UMETA(DisplayName = "Red"),
	Green   UMETA(DisplayName = "Green"),
	Blue    UMETA(DisplayName = "Blue"),
	White  UMETA(DisplayName = "White")
};

UCLASS()
class MYPROJECT2_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void HandleRedColor();
	void HandleGreenColor();
	void HandleBlueColor();
	void HandleWhiteColor();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Color Choice")
	EColorType SelectedColor;
	
	void SetObjectsVisibility(EColorType Color);

	void StartPlay();

	void HideAll();

	UPROPERTY()
	TArray<AActor*> RedActors;

	UPROPERTY()
	TArray<AActor*> GreenActors;

	UPROPERTY()
	TArray<AActor*> BlueActors;

	UPROPERTY()
	TArray<AActor*> WhiteActors;

	void PrintActorList(const FString& TagName, const TArray<AActor*>& ActorArray);
};
