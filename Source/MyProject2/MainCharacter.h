// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Engine/Spotlight.h"
#include "Components/SphereComponent.h"
#include "Interactable.h"
#include "MainCharacter.generated.h"


UCLASS()
class MYPROJECT2_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditInstanceOnly, Category = "Mesh")
	class USkeletalMeshComponent* Machine;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* Move;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* Look;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* Fire;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* Interact;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* Jumps;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* Crouchs;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float SpreadRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire")
	TSubclassOf<AActor> BlueprintToSpawn;

	void AddInteract(AActor* Other);
	void RemoveInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void LookFuction(const FInputActionValue& Value);

	UFUNCTION()
	void OnFire();

	UFUNCTION()
	void Crouching();

	UFUNCTION()
	void Jumping();

	UFUNCTION()
	void MoveFunction(const FInputActionValue& Value);

	UFUNCTION()
	void InteractFunction();

	IInteractable* CurrentInteractable;

	FVector2D PreviousMovementVector;

	bool bCanFire;

	FTimerHandle FireTimerHandle;

	void ResetFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
