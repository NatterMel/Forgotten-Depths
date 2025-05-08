// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MyWidgetitem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UMyWidgetitem : public UUserWidget
{
	GENERATED_BODY()

public:

    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Data", meta = (ExposeOnSpawn))
    FText DisplayedText;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Item Data", meta = (ExposeOnSpawn))
    UTexture2D* DisplayedIcon;
};
