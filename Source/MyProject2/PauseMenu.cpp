// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

bool UPauseMenu::Initialize()
{
    bool bSuccess = Super::Initialize();
    if (!bSuccess) return false;

    if (ResumeButton)
        ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::OnResumeClicked);

    if (OptionsButton)
        OptionsButton->OnClicked.AddDynamic(this, &UPauseMenu::OnOptionsClicked);

    if (QuitButton)
        QuitButton->OnClicked.AddDynamic(this, &UPauseMenu::OnQuitClicked);

    return true;
}


void UPauseMenu::OnResumeClicked()
{
    RemoveFromParent();
    UGameplayStatics::SetGamePaused(GetWorld(), false);

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }
    if (APawn* Pawn = PC->GetPawn())
    {
        if (AMainCharacter* MainChar = Cast<AMainCharacter>(Pawn))
        {
            MainChar->ClearPauseMenu();  
        }
    }
}

void UPauseMenu::OnOptionsClicked()
{
    if (OptionsMenu)
    {
        OptionsInstance = CreateWidget<UUserWidget>(GetWorld(), OptionsMenu);
        if (OptionsInstance)
        {
            OptionsInstance->AddToViewport();
            OptionsInstance->SetVisibility(ESlateVisibility::Visible);
            OptionsInstance->SetIsEnabled(true);
            APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            if (PC)
            {
                PC->bShowMouseCursor = true;
                PC->SetInputMode(FInputModeUIOnly());
            }
        }
    }
}

void UPauseMenu::OnQuitClicked()
{
    UGameplayStatics::SetGamePaused(GetWorld(), false);
    RemoveFromParent();
    if (LevelToLoad.ToSoftObjectPath().IsValid())
    {
        FString LevelPath = LevelToLoad.ToSoftObjectPath().GetLongPackageName();
        UGameplayStatics::OpenLevel(this, FName(*LevelPath));
    }
}