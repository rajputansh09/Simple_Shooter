// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"



UBTService_PlayerLocation::UBTService_PlayerLocation()
{
    NodeName = TEXT("Update Player Location"); // Set the name of the service node
}



void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds); // Call the parent class's TickNode method

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Get the player pawn in the world

    if (PlayerPawn == nullptr) // Check if PlayerPawn is valid
    {
        return; // If PlayerPawn is not valid, exit the function early
    }
    
    
    if (PlayerPawn && OwnerComp.GetAIOwner()) // Check if PlayerPawn and AI owner are valid
    {
        // Update PlayerLocation in the blackboard
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation()); // Set the PlayerLocation key in the blackboard to the player's current location
    }
}
