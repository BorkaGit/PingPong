// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromBallBase.h"

#include "FaromPlatformBase.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AFaromBallBase::AFaromBallBase()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>( TEXT("CollisionSphere") );
	RootComponent = CollisionSphere;
	CollisionSphere	->SetSphereRadius(30.0f);
	CollisionSphere->BodyInstance.bUseCCD = true;
	
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(CollisionSphere);

	bReplicates = true;
	SetReplicatingMovement(true);
}


void AFaromBallBase::BeginPlay()
{
	Super::BeginPlay();

	BallStartRotation();
	BallStartVelocity();

}

void AFaromBallBase::ProcessBallMovement(float const DeltaTime)
{
	SetActorLocation( GetActorLocation() + CurrentVelocity * DeltaTime ,true);
}

void AFaromBallBase::DoCollisionTest(float const DeltaTime)
{
	FVector const& SweepFrom	= GetActorLocation();
	FVector const& SweepTo		= GetActorLocation() + CurrentVelocity * DeltaTime;

	const TArray<AActor*>		ActorsToIgnore({ this });
	
	FHitResult					SweepResult;

	UKismetSystemLibrary::SphereTraceSingle( this, SweepFrom, SweepTo, 
											CollisionSphere->GetScaledSphereRadius(), 
											ETraceTypeQuery::TraceTypeQuery3, 
											false, 
											ActorsToIgnore, 											
											EDrawDebugTrace::None, 
											SweepResult,
											true
											);
	if ( SweepResult.bBlockingHit )
		SetBallVelocity(GetBallVelocity().MirrorByVector(SweepResult.ImpactNormal));
	
}

void AFaromBallBase::BallStartRotation()
{
	const float Yaw = FMath::FRandRange(-180.f, 180.f);
	const float Pitch = GetActorRotation().Pitch;
	const float Roll =  GetActorRotation().Roll;
	
	const FRotator BallRotation = FRotator(Pitch,Yaw,Roll);
	SetActorRotation(BallRotation);
}


void AFaromBallBase::BallStartVelocity()
{
	StartVelocity = FMath::FRandRange(MinStartVelocity,MaxStartVelocity);
	const FVector BallVelocity = GetActorForwardVector() * StartVelocity;
	SetBallVelocity(BallVelocity);
}



void AFaromBallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoCollisionTest		( DeltaTime );
	ProcessBallMovement	( DeltaTime );
}


