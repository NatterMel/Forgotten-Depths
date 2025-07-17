// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"
#include "Engine/SpotLight.h"
#include "Components/SphereComponent.h"
#include "Interactable.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	GetCapsuleComponent()->InitCapsuleSize(40.0f, 95.0f);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->AddRelativeLocation(FVector(-40.0f, 1.75f, 64.0f));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(Camera);
	Camera->bUsePawnControlRotation = true;
	if (ColorList.IsEmpty())
	{
		ColorList.Add(FLinearColor::White);
	}
	GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	ColorIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ColorIndicator"));
	ColorIndicator->SetupAttachment(Camera);
	ColorIndicator->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.005f));  
	ColorIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMainCharacter::ClearPauseMenu()
{
	PauseMenuInstance = nullptr;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	bCanFire = true;
	ColorChosen = ColorList[0];
	
	FString CurrentLevel = GetWorld()->GetMapName();
	CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	if (CurrentLevel == TEXT("Menu"))
	{
		if (HUDWidget)
		{
			HUDWidget->RemoveFromParent();
			HUDWidget = nullptr;
		}
		return; // Skip the rest of the setup if not in a playable level
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (HudClass)
	{
		HUDWidget = CreateWidget<UCrosshair>(GetWorld(), HudClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
			HUDWidget->HideInteractHint();
		}
	}

	if (ColorIndicator && IndicatorMaterialBase)
	{
		IndicatorMaterial = UMaterialInstanceDynamic::Create(IndicatorMaterialBase, this);
		ColorIndicator->SetMaterial(0, IndicatorMaterial);
		IndicatorMaterial->SetVectorParameterValue("Color", ColorChosen);
	}
}
void AMainCharacter::DeactivateHUD()
{
	if (HUDWidget)
	{
		HUDWidget->RemoveFromParent();
		HUDWidget = nullptr;
	}
}

void AMainCharacter::ResetFire()
{
	bCanFire = true;
	if (IndicatorMaterial)
	{
		IndicatorMaterial->SetVectorParameterValue("Color", ColorChosen);
	}
}

void AMainCharacter::ChangeColor(const FInputActionValue& Value)
{
	if (!bCanFire) return;
	float WheelValue = Value.Get<float>();
	int32 CurrentIndex = ColorList.Find(ColorChosen);
	int32 NumColors = ColorList.Num();

	int32 NextIndex = (CurrentIndex + static_cast<int32>(WheelValue)) % NumColors;
	NextIndex = (NextIndex + NumColors) % NumColors;

	ColorChosen = ColorList[NextIndex];
	if (IndicatorMaterial)
	{
		IndicatorMaterial->SetVectorParameterValue("Color", ColorChosen);
	}
	switch (NextIndex)
	{
	case 0:
		GameMode->HandleRedColor();
		break;
	case 1:
		GameMode->HandleGreenColor();
		break;
	case 2:
		GameMode->HandleBlueColor();
		break;
	case 3:
		GameMode->HandleWhiteColor();
		break;
	default:
		break;
	}
}

void AMainCharacter::AddInteract(AActor* Other)
{
	if (IInteractable* Interactable = Cast<IInteractable>(Other))
	{
		CurrentInteractable = Interactable;
		if (HUDWidget)
		{
			HUDWidget->ShowInteractHint();
		}
	}

}

void AMainCharacter::RemoveInteract()
{
	if (CurrentInteractable)
	{
		CurrentInteractable = nullptr;
		if (HUDWidget)
		{
			HUDWidget->HideInteractHint();
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(Move, ETriggerEvent::Triggered, this, &AMainCharacter::MoveFunction);

		if (IsValid(Look))
		{
			Input->BindAction(Look, ETriggerEvent::Triggered, this, &AMainCharacter::LookFuction);
		}

		Input->BindAction(Fire, ETriggerEvent::Triggered, this, &AMainCharacter::OnFire);

		Input->BindAction(Interact, ETriggerEvent::Triggered, this, &AMainCharacter::InteractFunction);

		Input->BindAction(Crouchs, ETriggerEvent::Triggered, this, &AMainCharacter::Crouching);
		Input->BindAction(Jumps, ETriggerEvent::Triggered, this, &AMainCharacter::Jumping);
		Input->BindAction(Jumps, ETriggerEvent::Completed, this, &AMainCharacter::StopJumping);
		Input->BindAction(Change, ETriggerEvent::Triggered, this, &AMainCharacter::ChangeColor);
		Input->BindAction(Pause, ETriggerEvent::Triggered, this, &AMainCharacter::PauseFunction);
	}

}

void AMainCharacter::MoveFunction(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	MovementVector.Normalize();

	if (Controller && !MovementVector.IsNearlyZero())
	{
			const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

			const FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(YawRotation);
			const FVector RightDirection = UKismetMathLibrary::GetRightVector(YawRotation);

			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
			PreviousMovementVector = MovementVector;
	}
}

void AMainCharacter::InteractFunction()
{
	if (CurrentInteractable)
	{

		CurrentInteractable->OnInteract_Implementation();
	}
}

void AMainCharacter::PauseFunction()
{
	const bool bShouldPause = !UGameplayStatics::IsGamePaused(GetWorld());
	UGameplayStatics::SetGamePaused(GetWorld(), bShouldPause);

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC) return;

	if (bShouldPause)
	{
		if (PauseMenu && !PauseMenuInstance)
		{
			PauseMenuInstance = CreateWidget<UUserWidget>(GetWorld(), PauseMenu);
			if (PauseMenuInstance)
			{
				PauseMenuInstance->AddToViewport();

				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(PauseMenuInstance->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PC->SetInputMode(InputMode);
				PC->bShowMouseCursor = true;
			}
		}
	}
	else
	{
		if (PauseMenuInstance)
		{
			PauseMenuInstance->RemoveFromParent();
			PauseMenuInstance = nullptr;
		}

		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}
}

void AMainCharacter::RemoveLights()
{
	if (spawnedlights != 1)
	{
		--spawnedlights;
	}else
	{
		--spawnedlights;
		ResetFire();
	}
}

void AMainCharacter::LookFuction(const FInputActionValue& Value)
{
	if (!Controller)
	{
		return;
	}
		FVector2D LookAxisVector = Value.Get<FVector2D>();

		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
}

void AMainCharacter::OnFire()
{
	if (bCanFire)
	{
		bCanFire = false;
		UWorld* World = GetWorld();
		if (!World)
			return;

		FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = false;

		FVector ForwardVector = Camera->GetForwardVector();
		FVector RightVector = Camera->GetRightVector();
		FVector UpVector = Camera->GetUpVector();

		const int32 NumRays = 7;
		FVector Start = Camera->GetComponentLocation();

		bool bAnyHit = false;

		if (IndicatorMaterial)
		{
			IndicatorMaterial->SetVectorParameterValue("Color", FLinearColor::Black);
		}

		for (int32 i = 0; i < NumRays; i++)
		{
			FVector TraceDirection = ForwardVector;

			if (i > 0)
			{
				float AngleDeg = 60.0f * (i - 1);
				float AngleRad = FMath::DegreesToRadians(AngleDeg);

				FVector OffsetDirection = (ForwardVector * 0.5f) +
					(RightVector * FMath::Cos(AngleRad)) +
					(UpVector * FMath::Sin(AngleRad));
				OffsetDirection.Normalize();

				TraceDirection = (ForwardVector + (OffsetDirection * SpreadRadius)).GetSafeNormal();
			}

			FVector End = Start + (TraceDirection * LengthLight);

			FHitResult HitResult;
			bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams);
			if (bHit)
			{
				bAnyHit = true;

				if (IsValid(BlueprintToSpawn))
				{
					FVector SpawnLocation = HitResult.Location - (TraceDirection * 10.f);
					FActorSpawnParameters SpawnParams;
					AFadingLight* lights = GetWorld()->SpawnActor<AFadingLight>(BlueprintToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
					lights->SetStartIntensity(StartIntensity, FadeRate);
					lights->SetColor(ColorChosen);
					++spawnedlights;
				}

				FVector HitLocation = HitResult.Location;
				//DrawDebugLine(World, Start, HitLocation, FColor::Green, true, 5.f, 0, 5.f);
			}
		}

		if (!bAnyHit)
		{
			ResetFire();
		}
	}
}

void AMainCharacter::Crouching()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void AMainCharacter::Jumping()
{
	Jump();
}


