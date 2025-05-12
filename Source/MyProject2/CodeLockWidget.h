// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CodeLockWidget.generated.h"

/**
 * 
 */
class ACodeLock;
UCLASS()
class MYPROJECT2_API UCodeLockWidget : public UUserWidget
{
    GENERATED_BODY()


public:
    UPROPERTY(BlueprintReadWrite, Category = "Code Lock", meta = (ExposeOnSpawn = true))
    ACodeLock* CodeLockRef;

    UFUNCTION(BlueprintCallable)
    void CloseWidget();

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget)) UButton* Btn_0;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_1;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_2;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_3;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_4;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_5;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_6;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_7;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_8;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_9;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_Clear;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_Check;
    UPROPERTY(meta = (BindWidget)) UButton* Btn_Exit;
    UPROPERTY(meta = (BindWidget)) UTextBlock* DisplayText;

    void HandleDigit(int32 Digit);


    UFUNCTION() void OnBtn0Clicked();
    UFUNCTION() void OnBtn1Clicked();
    UFUNCTION() void OnBtn2Clicked();
    UFUNCTION() void OnBtn3Clicked();
    UFUNCTION() void OnBtn4Clicked();
    UFUNCTION() void OnBtn5Clicked();
    UFUNCTION() void OnBtn6Clicked();
    UFUNCTION() void OnBtn7Clicked();
    UFUNCTION() void OnBtn8Clicked();
    UFUNCTION() void OnBtn9Clicked();
    UFUNCTION() void OnBtnClearClicked();
    UFUNCTION() void OnBtnCheckClicked();
    UFUNCTION() void OnBtnExitClicked();
    void UpdateDisplayText();


};

