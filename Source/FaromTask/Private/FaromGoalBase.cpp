// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromGoalBase.h"

#include "FaromBallBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


AFaromGoalBase::AFaromGoalBase()
{

	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT("BoxComponent") );
	RootComponent = BoxComponent;
	
	GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalMesh"));
	GoalMesh->SetupAttachment(BoxComponent);

	bReplicates = true;
}

void AFaromGoalBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (HasAuthority())
	{
		if ( AFaromBallBase* Ball = Cast<AFaromBallBase>( OtherActor ) )
		{
			++Score;
		}
	}
}

void AFaromGoalBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

void AFaromGoalBase::OnRep_Score()
{
	OnGoal();
}

void AFaromGoalBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFaromGoalBase, Score);
}
