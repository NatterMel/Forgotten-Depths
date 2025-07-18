// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProximityComponent.h"
#include "Interactable.h"
#include "CodeLock.generated.h"

class UCodeLockWidget;
UCLASS()
class MYPROJECT2_API ACodeLock : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeLock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Code Lock")
    void EnterDigit(int32 Digit);

    UFUNCTION(BlueprintCallable, Category = "Code Lock")
    void ResetInput();
    UFUNCTION(BlueprintCallable, Category = "Code Lock")
    void OnCodeCorrect();

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere)
    UProximityComponent* Trigger;

    UPROPERTY(EditAnywhere, Category = "Code Lock")
    AActor* ActorToActivate;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> ItemInfoWidgetClass;

    virtual void OnInteract_Implementation() override;
    void CheckCode();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Code Lock")
    TArray<int32> EnteredCode;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction")
    bool bCanBeInteractedWith = true;
protected:


    UPROPERTY() UCodeLockWidget* ActiveWidget;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code Lock")
    TArray<int32> CorrectCode;





};
