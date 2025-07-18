// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeLockWidget.h"
#include "Blueprint/UserWidget.h"
#include "CodeLock.h"
#include "Kismet/GameplayStatics.h"

void UCodeLockWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (Btn_0) Btn_0->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn0Clicked);
    if (Btn_1) Btn_1->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn1Clicked);
    if (Btn_2) Btn_2->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn2Clicked);
    if (Btn_3) Btn_3->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn3Clicked);
    if (Btn_4) Btn_4->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn4Clicked);
    if (Btn_5) Btn_5->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn5Clicked);
    if (Btn_6) Btn_6->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn6Clicked);
    if (Btn_7) Btn_7->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn7Clicked);
    if (Btn_8) Btn_8->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn8Clicked);
    if (Btn_9) Btn_9->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtn9Clicked);
    if (Btn_Clear) Btn_Clear->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtnClearClicked);
    if (Btn_Check) Btn_Check->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtnCheckClicked);
    if (Btn_Exit) Btn_Exit->OnClicked.AddDynamic(this, &UCodeLockWidget::OnBtnExitClicked);
}

void UCodeLockWidget::HandleDigit(int32 Digit)
{
    if (CodeLockRef)
    {
        CodeLockRef->EnterDigit(Digit);
        UpdateDisplayText();
    }
}

void UCodeLockWidget::OnBtnClearClicked()
{
    if (CodeLockRef)
    {
        CodeLockRef->ResetInput();
        UpdateDisplayText();
    }
}

void UCodeLockWidget::OnBtnCheckClicked()
{
        if (CodeLockRef)
        {
            CodeLockRef->CheckCode();
            UpdateDisplayText();
        }
}

void UCodeLockWidget::OnBtnExitClicked()
{
    CloseWidget();
}

void UCodeLockWidget::UpdateDisplayText()
{
    if (!DisplayText || !CodeLockRef) return;

    FString Display;

    const TArray<int32>& Entered = CodeLockRef->EnteredCode;

    for (int32 i = 0; i < Entered.Num(); ++i)
    {
        Display += FString::FromInt(Entered[i]) + TEXT(" ");
    }

    for (int32 i = Entered.Num(); i < 4; ++i)
    {
        Display += "_ ";
    }

    DisplayText->SetText(FText::FromString(Display));
}

void UCodeLockWidget::OnBtn0Clicked() { HandleDigit(0); }
void UCodeLockWidget::OnBtn1Clicked() { HandleDigit(1); }
void UCodeLockWidget::OnBtn2Clicked() { HandleDigit(2); }
void UCodeLockWidget::OnBtn3Clicked() { HandleDigit(3); }
void UCodeLockWidget::OnBtn4Clicked() { HandleDigit(4); }
void UCodeLockWidget::OnBtn5Clicked() { HandleDigit(5); }
void UCodeLockWidget::OnBtn6Clicked() { HandleDigit(6); }
void UCodeLockWidget::OnBtn7Clicked() { HandleDigit(7); }
void UCodeLockWidget::OnBtn8Clicked() { HandleDigit(8); }
void UCodeLockWidget::OnBtn9Clicked() { HandleDigit(9); }

void UCodeLockWidget::CloseWidget()
{   
    RemoveFromParent();
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }


}