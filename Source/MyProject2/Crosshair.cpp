// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"
#include "Components/MultiLineEditableText.h"
#include "Components/TextBlock.h"

void UCrosshair::NativeConstruct()
{
    Super::NativeConstruct();


    if (AutoHintText)
    {
        AutoHintText->SetVisibility(ESlateVisibility::Hidden);
    }


    ShowAutoHint();
}

void UCrosshair::ShowInteractHint()
{
	if (InteractText)
	{
		InteractText->SetVisibility(ESlateVisibility::Visible);
	}
}

void UCrosshair::HideInteractHint()
{
	if (InteractText)
	{
		InteractText->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UCrosshair::ShowAutoHint()
{
    if (AutoHintText)
    {
        AutoHintText->SetVisibility(ESlateVisibility::Visible);

        if (UWorld* World = GetWorld())
        {
            FTimerHandle TimerHandle;
            World->GetTimerManager().SetTimer(TimerHandle, [this]()
                {
                    if (AutoHintText)
                    {
                        AutoHintText->SetVisibility(ESlateVisibility::Hidden);
                    }
                }, 5.f, false);
        }
    }
}