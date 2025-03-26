// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/RectLight.h"
#include "ColorRectLight.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API AColorRectLight : public ARectLight
{
	GENERATED_BODY()
public:
	AColorRectLight();

	UPROPERTY(EditAnywhere, Category = "Color")
	FLinearColor UseColor;
};
