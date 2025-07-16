// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT2_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
    virtual bool Initialize() override;

    UFUNCTION()
    void OnResumeClicked();

    UFUNCTION()
    void OnOptionsClicked();

    UFUNCTION()
    void OnQuitClicked();

protected:
    UPROPERTY(meta = (BindWidget))
    class UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* OptionsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUserWidget> OptionsMenu;

    UUserWidget* OptionsInstance;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Maps")
    TSoftObjectPtr<UWorld> LevelToLoad;
};
