// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Fire.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Fire::UBTTask_Fire()
{
    NodeName = TEXT("Fire"); // Set the name of the task node
}

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
   Super::ExecuteTask(OwnerComp, NodeMemory); // Call the parent class's ExecuteTask method

   if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed; // If there is no AI owner, return failure
    }     

    AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (Character == nullptr)
    {
        return EBTNodeResult::Failed; // If the character is not valid, return failure
    }
    Character->Fire(); // Call the Fire method on the character to execute the firing action

    return EBTNodeResult::Succeeded; // Return success after executing the task

}
