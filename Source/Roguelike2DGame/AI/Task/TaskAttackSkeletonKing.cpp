// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAttackSkeletonKing.h"
#include "../../Characters/Enemies/MeleeEnemies/MeleeEnemy.h"
#include <AIController.h>
#include <Tasks/GameplayTask_WaitDelay.h>



EBTNodeResult::Type UTaskAttackSkeletonKing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
  
    if (!owningCharacter)
    {
        owningCharacter = Cast<AMeleeEnemy>(OwnerComp.GetAIOwner()->GetPawn());
    }

    if (owningCharacter)
    {
        owningCharacter->OnAttack();
        owningCharacter->OnAttackHit();
        owningCharacter->OnEndAnimAttack();
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}
