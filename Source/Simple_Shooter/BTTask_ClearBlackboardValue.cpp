// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h" // Include the header for the Blackboard component to access its methods
#include "BehaviorTree/BehaviorTreeComponent.h" // Include the header for the Behavior Tree component to access its methods



UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
    // Constructor implementation can be added here if needed
    NodeName = TEXT("Clear Blackboard Value"); // Set the name of the task for debugging purposes
}


EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory); // Call the base class implementation to ensure proper task execution flow
    // Clear the blackboard value specified by the key
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); // Clear the value associated with the selected blackboard key
    return EBTNodeResult::Succeeded; // Return success after clearing the value
}


