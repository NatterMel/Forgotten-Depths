// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UMainMenu::Initialize()
{
    if (!Super::Initialize()) return false;

    if (StartButton) StartButton->OnClicked.AddDynamic(this, &UMainMenu::OnStartClicked);
    if (OptionsButton) OptionsButton->OnClicked.AddDynamic(this, &UMainMenu::OnOptionsClicked);
    if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClicked);

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->SetInputMode(FInputModeUIOnly());
        PC->bShowMouseCursor = true;
    }

    return true;
}

void UMainMenu::OnStartClicked()
{
    if (StartMap.ToSoftObjectPath().IsValid())
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
        if (PC)
        {
            PC->SetInputMode(FInputModeGameOnly());
            PC->bShowMouseCursor = false;
        }
        FString MapPath = StartMap.ToSoftObjectPath().GetAssetPathString();
        UGameplayStatics::OpenLevelBySoftObjectPtr(this, StartMap);
    }
}

void UMainMenu::OnOptionsClicked()
{
    if (OptionsWidgetClass)
    {
        OptionsWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidgetClass);
        if (OptionsWidget)
        {
            OptionsWidget->AddToViewport();
            APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
            if (PC)
            {
                PC->SetInputMode(FInputModeUIOnly());
                PC->bShowMouseCursor = true;
            }
        }
    }
}

void UMainMenu::OnQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
