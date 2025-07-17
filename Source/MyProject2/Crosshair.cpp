// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"
#include "Components/TextBlock.h"



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
