// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FaromGoalBase.generated.h"

class UBoxComponent;

UCLASS()
class FAROMTASK_API AFaromGoalBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFaromGoalBase();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnGoal();
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* GoalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Replicated,ReplicatedUsing=OnRep_Score)
	int32 Score;

	UFUNCTION()
	void OnRep_Score();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
