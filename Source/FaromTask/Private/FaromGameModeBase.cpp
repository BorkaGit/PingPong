// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromGameModeBase.h"

#include "FaromBallBase.h"
#include "Kismet/GameplayStatics.h"

void AFaromGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	++PlayerCount;
	CheckAndStartGame();
}


void AFaromGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	--PlayerCount;
}

void AFaromGameModeBase::MulticastPauseGame_Implementation(bool bIsPaused)
{
	UGameplayStatics::SetGamePaused(GetWorld(), bIsPaused);
}

void AFaromGameModeBase::CheckAndStartGame()
{
	if (PlayerCount < RequiredPlayerCount)
	{
		MulticastPauseGame(true);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(DebugMessageKey,FLT_MAX,FColor::Red,TEXT("Waiting for all players to join"));
	}
	else
	{
		MulticastPauseGame(false);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(DebugMessageKey,0.f,FColor::Transparent,TEXT(""));
	}
	
}
