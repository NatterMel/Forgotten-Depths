// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnVideoTabClicked();

    UFUNCTION()
    void OnAudioTabClicked();

    UFUNCTION()
    void OnGeneralTabClicked();

protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* VideoTabButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* AudioTabButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* GeneralTabButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* BackButton;

    UPROPERTY(meta = (BindWidget))
    class UWidget* VideoTabContent;

    UPROPERTY(meta = (BindWidget))
    class UWidget* AudioTabContent;

    UPROPERTY(meta = (BindWidget))
    class UWidget* GeneralTabContent;

    UFUNCTION()
    void OnBackClicked();

    void ShowTab(UWidget* TabToShow);

    //Video
    UPROPERTY(meta = (BindWidget))
    class UComboBoxString* ResolutionComboBox;

    UPROPERTY(meta = (BindWidget))
    class UCheckBox* FullscreenCheckBox;

    UPROPERTY(meta = (BindWidget))
    class UComboBoxString* GraphicsQualityComboBox;

    UPROPERTY(meta = (BindWidget))
    class UButton* ApplyVideoSettingsButton;

    UFUNCTION()
    void OnApplyVideoSettingsClicked();
};
