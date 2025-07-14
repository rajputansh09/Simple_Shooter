// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
   
    Super::PawnKilled(PawnKilled); // Call the base class implementation

    APlayerController * PlayerController = Cast<APlayerController>(PawnKilled->GetController()); // Cast the killed pawn to AShooterCharacter to access character-specific functionality
    if (PlayerController != nullptr) // Check if the cast was successful
    {

        EndGame(false); // If the player controller is valid, end the game with the player as a loser
    }

// For loop over ShooterAIController instances in the world
    for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!AIController->IsDead()) // Check if the AI controller's controlled character is dead
        {
            return; // If any AI controller is not dead, return early
        }
    }
    EndGame(true); // If all AI controllers are dead, end the game with the player as a winner
}


void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() && bIsPlayerWinner; // Check if the controller is a player controller and if the player is a winner
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner); // Call the GameHasEnded method on the controller, passing in the pawn and whether the player is a winner, // this will trigger the end game logic for each controller in the world
    }
}
