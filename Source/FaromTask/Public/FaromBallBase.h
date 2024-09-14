// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FaromBallBase.generated.h"

class AFaromPlatformBase;
class USphereComponent;

UCLASS()
class FAROMTASK_API AFaromBallBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AFaromBallBase();


	virtual void				BallStartVelocity();
protected:
	
	virtual void BeginPlay() override;
	virtual void				ProcessBallMovement		( float const DeltaTime );
	virtual void				DoCollisionTest			( float const DeltaTime );
	

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FVector const&			GetBallVelocity() const							{ return CurrentVelocity; }

	
	FORCEINLINE virtual void			SetBallVelocity(FVector const& NewVelocity)		{ CurrentVelocity = NewVelocity;}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BallMesh;

	UPROPERTY( EditAnywhere , Category = "BallProperties", meta = (ClampMin = "0", ClampMax = "10000")) 
	float MinStartVelocity                 = 0.0f;
	
	UPROPERTY( EditAnywhere , Category = "BallProperties", meta = (ClampMin = "0", ClampMax = "10000")) 
	float MaxStartVelocity                 = 5.0f;


	
public:	
	
	virtual void Tick(float DeltaTime) override;


private:

	
	FVector CurrentVelocity				= FVector::ZeroVector;
	void BallStartRotation();
	
	float StartVelocity;
};
