// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "MySaveGame.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

bool UMainMenu::Initialize()
{
    if (!Super::Initialize()) return false;

    if (StartButton) StartButton->OnClicked.AddDynamic(this, &UMainMenu::OnStartClicked);
    if (ContinueButton) ContinueButton->OnClicked.AddDynamic(this, &UMainMenu::OnContinueClicked);
    if (OptionsButton) OptionsButton->OnClicked.AddDynamic(this, &UMainMenu::OnOptionsClicked);
    if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClicked);

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->SetInputMode(FInputModeUIOnly());
        PC->bShowMouseCursor = true;
    }
    int SavedLevel = LoadLevelProgress(); 
    if (ContinueButton)
    {
        if (SavedLevel == 0)
        {
            ContinueButton->SetIsEnabled(false);
            ContinueButton->SetVisibility(ESlateVisibility::Visible);
            ContinueButton->SetBackgroundColor(FLinearColor::Gray);
        }
    }

    return true;
}

void UMainMenu::OnStartClicked()
{
    Loadlevel(0);
}
void UMainMenu::OnContinueClicked()
{
    int level = LoadLevelProgress();
    if (level >= 0)
    {
        Loadlevel(level);
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
            OptionsWidget->SetVisibility(ESlateVisibility::Visible);
            OptionsWidget->SetIsEnabled(true);
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

void UMainMenu::Loadlevel(int level)
{
    if (StartMap[level].ToSoftObjectPath().IsValid())
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
        if (PC)
        {
            PC->SetInputMode(FInputModeGameOnly());
            PC->bShowMouseCursor = false;
        }
        FString MapPath = StartMap[level].ToSoftObjectPath().GetAssetPathString();
        UGameplayStatics::OpenLevelBySoftObjectPtr(this, StartMap[level]);
    }
}

int UMainMenu::LoadLevelProgress()
{
    if (UGameplayStatics::DoesSaveGameExist(TEXT("MySaveSlot"), 0))
    {
        UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("MySaveSlot"), 0));
        if (LoadedGame)
        {
            return LoadedGame->PlayerLevel;
        }
    }
    return -1;
}
void UMainMenu::SaveLevelProgress()
{
    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
    SaveGameInstance->PlayerLevel = 0;
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MySaveSlot"), 0);
}