// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"




UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen"); // Set the name of the service node
}



void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds); // Call the parent class's TickNode method

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); // Get the player pawn in the world


    if (PlayerPawn == nullptr) // Check if PlayerPawn is valid
    {
        return; // If either is not valid, exit the function early
    }

   if (OwnerComp.GetAIOwner() == nullptr) // Check if AIController is valid
    {
        return; // If AIController is not valid, exit the function early
    }

    //check for line of sight
    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        // Update PlayerLocation in the blackboard if AI can see the player
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn); // Set the PlayerLocation key in the blackboard to the player's current location
    }
    else
    {
        // Clear PlayerLocation if AI cannot see the player
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); // Clear the PlayerLocation key in the blackboard
    }

}



