// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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

	UPROPERTY(EditAnywhere, Category = "RayTrace")
	float SpreadRadius = 50.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnFire();

	void MoveFunction(const FInputActionValue& Value);

	void LookFunction(const FInputActionValue& Value);

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
