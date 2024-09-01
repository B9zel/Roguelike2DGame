// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAttackEnemy.h"
#include "../../Characters/BasePaperCharacter.h"

#include <AIController.h>



EBTNodeResult::Type UTaskAttackEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ABasePaperCharacter* character = Cast<ABasePaperCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (character)
    {
        character->OnAttack();
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}
