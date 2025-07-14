// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLE_SHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override; // Override the GameHasEnded method to handle game end logic	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass; // Class for the lose screen widget
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass; // Class for the win screen widget

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f; // Delay before restarting the game after it has ended
	
	FTimerHandle RestartTimer; // Timer handle for the restart timer

	UPROPERTY(EditAnywhere)
	UUserWidget* HUD; // HUD widget to display information

};
