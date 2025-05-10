// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWidgetitem.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMyWidgetitem::NativeConstruct()
{
	Super::NativeConstruct();

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UMyWidgetitem::OnCloseClicked);
    }
}
void UMyWidgetitem::OnCloseClicked()
{
    // Unpause the game
    if (GetWorld())
    {
        UGameplayStatics::SetGamePaused(GetWorld(), false);
    }
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly()); // Input back to gameplay
    }
    RemoveFromParent();
}
