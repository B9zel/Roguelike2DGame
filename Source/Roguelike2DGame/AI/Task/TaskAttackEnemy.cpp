// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAttackEnemy.h"
#include "../../Characters/BasePaperCharacter.h"

#include <AIController.h>



EBTNodeResult::Type UTaskAttackEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ABasePaperCharacter* character = Cast<ABasePaperCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (!character) return EBTNodeResult::Failed;

    if (!character->endAnimAttack.Contains(this, "EndAttack"))
    {
        character->endAnimAttack.AddDynamic(this, &UTaskAttackEnemy::EndAttack);
    }

    character->OnAttack();

    return EBTNodeResult::InProgress;
}

void UTaskAttackEnemy::EndAttack()
{
    FinishExecute(true);
}
