// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/Widget.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"


void UOptionsWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //Add Events
    if (VideoTabButton)
        VideoTabButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnVideoTabClicked);

    if (AudioTabButton)
        AudioTabButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnAudioTabClicked);

    if (ApplyVideoSettingsButton)
        ApplyVideoSettingsButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnApplyVideoSettingsClicked);

    if (BackButton)
        BackButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnBackClicked);

    if (MasterVolumeSlider)
        MasterVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionsWidget::OnMasterVolumeChanged);

    if (MusicVolumeSlider)
        MusicVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionsWidget::OnMusicVolumeChanged);

    if (SFXVolumeSlider)
        SFXVolumeSlider->OnValueChanged.AddDynamic(this, &UOptionsWidget::OnSFXVolumeChanged);

    if (ApplyAudioSettingsButton)
        ApplyAudioSettingsButton->OnClicked.AddDynamic(this, &UOptionsWidget::OnApplyAudioSettingsClicked);

    //Video Constructor
    if (ResolutionComboBox)
    {
        ResolutionComboBox->ClearOptions();
        ResolutionComboBox->AddOption(TEXT("1920x1080"));
        ResolutionComboBox->AddOption(TEXT("1280x720"));
        ResolutionComboBox->AddOption(TEXT("800x600"));
        ResolutionComboBox->SetSelectedIndex(0);
    }

    if (GraphicsQualityComboBox)
    {
        GraphicsQualityComboBox->ClearOptions();
        GraphicsQualityComboBox->AddOption(TEXT("Low"));
        GraphicsQualityComboBox->AddOption(TEXT("Medium"));
        GraphicsQualityComboBox->AddOption(TEXT("High"));
        GraphicsQualityComboBox->AddOption(TEXT("Epic"));
        GraphicsQualityComboBox->SetSelectedIndex(2);
    }
    ShowTab(nullptr);
    UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
}

void UOptionsWidget::OnVideoTabClicked()
{
    ShowTab(VideoTabContent);
}

void UOptionsWidget::OnAudioTabClicked()
{
    ShowTab(AudioTabContent);
}


void UOptionsWidget::OnBackClicked()
{
    RemoveFromParent();
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->SetInputMode(FInputModeUIOnly());
        PC->bShowMouseCursor = true;
    }
}

void UOptionsWidget::ShowTab(UWidget* TabToShow)
{
    if (VideoTabContent) VideoTabContent->SetVisibility(ESlateVisibility::Collapsed);
    if (AudioTabContent) AudioTabContent->SetVisibility(ESlateVisibility::Collapsed);

    if (TabToShow) TabToShow->SetVisibility(ESlateVisibility::Visible);
}

void UOptionsWidget::OnApplyVideoSettingsClicked()
{
    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (!Settings) return;

    //Resolution
	if (ResolutionComboBox)
	{
		const FString SelectedResolution = ResolutionComboBox->GetSelectedOption();
		FString XStr, YStr;

		if (SelectedResolution.Split("x", &XStr, &YStr))
		{
			int32 Width = FCString::Atoi(*XStr);
			int32 Height = FCString::Atoi(*YStr);
			Settings->SetScreenResolution(FIntPoint(Width, Height));
		}
	}

    //Fullscreen
    if (FullscreenCheckBox)
    {
        bool bIsFullscreen = FullscreenCheckBox->IsChecked();
        Settings->SetFullscreenMode(bIsFullscreen ? EWindowMode::Fullscreen : EWindowMode::Windowed);
    }

    //Graphics Quality
    if (GraphicsQualityComboBox)
    {
        const FString SelectedQuality = GraphicsQualityComboBox->GetSelectedOption();

        int32 QualityLevel = 2;
        if (SelectedQuality == "Low")      QualityLevel = 0;
        else if (SelectedQuality == "Medium") QualityLevel = 1;
        else if (SelectedQuality == "High")   QualityLevel = 2;
        else if (SelectedQuality == "Epic")   QualityLevel = 3;

        Settings->SetOverallScalabilityLevel(QualityLevel);
    }


}
void UOptionsWidget::OnApplyAudioSettingsClicked()
{
    if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
    {
        Settings->ApplySettings(false);
        Settings->SaveSettings();
    }
}
void UOptionsWidget::OnMasterVolumeChanged(float Value)
{
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, MasterSoundClass, Value, 1.0f, 0.0f, true);
}

void UOptionsWidget::OnMusicVolumeChanged(float Value)
{
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, MusicSoundClass, Value, 1.0f, 0.0f, true);
}

void UOptionsWidget::OnSFXVolumeChanged(float Value)
{
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, SFXSoundClass, Value, 1.0f, 0.0f, true);
}