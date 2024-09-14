// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromPlatformBase.h"

#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


AFaromPlatformBase::AFaromPlatformBase()
{

	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT("StaticMesh"));
	RootComponent = BoxComponent;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT("PlatformMesh"));
	PlatformMesh->SetupAttachment(BoxComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->SetIsReplicated(true);
	
	bReplicates = true;
	SetReplicatingMovement(true);
	
	PrimaryActorTick.bCanEverTick = true;

}


void AFaromPlatformBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AFaromPlatformBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AFaromPlatformBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFaromPlatformBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

