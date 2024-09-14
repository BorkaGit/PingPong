// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AFaromPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{	
		check(PlayerContext);
		UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
		check(EnhancedInputLocalPlayerSubsystem);
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(PlayerContext, 0);
	}
}

void AFaromPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalController())
	{
		EnableInput(this);
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	}
}

void AFaromPlayerController::Move(const FInputActionValue& InputActionValue)
{
	
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
		FVector Location = ControlledPawn->GetActorLocation();
		ServerUpdateTransform(Location);
		
		
		if (!HasAuthority())
			ServerMove(RightDirection, InputAxisVector.X);

		
	}
}

void AFaromPlayerController::ServerUpdateTransform_Implementation(FVector Location)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
		ControlledPawn->SetActorLocation(Location);
}

void AFaromPlayerController::ServerMove_Implementation(FVector Direction, float AxisValue)
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(Direction, AxisValue);
		ControlledPawn->SetActorTransform(ControlledPawn->GetActorTransform());
	}
}


