// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* ContinueButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* OptionsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maps")
    TArray<TSoftObjectPtr<UWorld>> StartMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main Menu", meta = (ExposeOnSpawn = true))
    TSubclassOf<UUserWidget> OptionsWidgetClass;

    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnContinueClicked();

    UFUNCTION()
    void OnOptionsClicked();

    UFUNCTION()
    void OnQuitClicked();

    int LoadLevelProgress();

    void Loadlevel(int level);
    
    UPROPERTY()
    UUserWidget* OptionsWidget;
};
