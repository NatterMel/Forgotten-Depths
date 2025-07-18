// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UCrosshair : public UUserWidget
{
	GENERATED_BODY()

public: 
	UPROPERTY(meta = (BindWidget))
	class UImage* CrosshairImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InteractText;

	UPROPERTY(meta = (BindWidget))
	class UMultiLineEditableText* AutoHintText;

	UFUNCTION(BlueprintCallable)
	void ShowInteractHint();

	UFUNCTION(BlueprintCallable)
	void HideInteractHint();

	UFUNCTION(BlueprintCallable)
	void ShowAutoHint();

	virtual void NativeConstruct() override;
	FTimerHandle HintTimerHandle;
	
};
