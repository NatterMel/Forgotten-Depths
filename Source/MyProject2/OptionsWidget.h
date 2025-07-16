// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Sound/SoundMix.h"
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

protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* VideoTabButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* AudioTabButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* BackButton;

    UPROPERTY(meta = (BindWidget))
    class UWidget* VideoTabContent;

    UPROPERTY(meta = (BindWidget))
    class UWidget* AudioTabContent;

    UPROPERTY(meta = (BindWidget))
    USlider* MasterVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    USlider* MusicVolumeSlider;

    UPROPERTY(meta = (BindWidget))
    USlider* SFXVolumeSlider;

    // Optionally: Apply audio button
    UPROPERTY(meta = (BindWidget))
    UButton* ApplyAudioSettingsButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundMix* SoundMix;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundClass* MasterSoundClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundClass* MusicSoundClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundClass* SFXSoundClass;

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

    UFUNCTION()
    void OnApplyAudioSettingsClicked();

    UFUNCTION()
    void OnMasterVolumeChanged(float Value);

    UFUNCTION()
    void OnMusicVolumeChanged(float Value);

    UFUNCTION()
    void OnSFXVolumeChanged(float Value);
};
