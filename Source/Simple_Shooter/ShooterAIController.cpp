// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"




void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    
    if (AIBehavior) // Check if AIBehavior is set
    {
        RunBehaviorTree(AIBehavior); // Start the behavior tree if it is set

        APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Get the player pawn in the world, if needed, PlayerPawn is a pointer to the player pawn actor
               
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation()); // Set the initial start location in the blackboard component
        
    }

}


void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}


bool AShooterAIController::IsDead() const
{

    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn()); // Cast the controlled pawn to AShooterCharacter to access character-specific functionality
    if (ControlledCharacter)
    {
        return ControlledCharacter->IsDead(); // Call the IsDead method on the character to check if it is dead
    }
    return true; // If the controlled character is not valid, return true (indicating dead)
}
