// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override; // Override the PawnKilled method to handle the killing of a pawn

	
private:
	void EndGame(bool bIsPlayerWinner); // Private method to end the game, indicating whether the player is a winner or not
	
};
