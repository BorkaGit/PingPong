// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FaromGameModeBase.generated.h"


class AFaromBallBase;

UCLASS()
class FAROMTASK_API AFaromGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSoftObjectPtr<AFaromBallBase> Ball;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPauseGame(bool bIsPaused);
	
private:
	void CheckAndStartGame();

	uint32 PlayerCount = 0;
	uint32 RequiredPlayerCount = 2;
	uint64 DebugMessageKey = 1;
	
};
