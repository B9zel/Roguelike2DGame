// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAttackSkeletKingCustomDamage.h"
#include "../../Characters/Enemies/MeleeEnemies/MeleeEnemy.h"
#include <AIController.h>



EBTNodeResult::Type UTaskAttackSkeletKingCustomDamage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (!owningCharacter)
    {
        owningCharacter = Cast<AMeleeEnemy>(OwnerComp.GetAIOwner()->GetPawn());
    }

    if (owningCharacter)
    {
        defaultDamage = owningCharacter->GetDamage();
        owningCharacter->SetDamage(Damage);

        owningCharacter->OnAttack();
        owningCharacter->OnAttackHit();
        owningCharacter->OnEndAnimAttack();

        owningCharacter->SetDamage(defaultDamage);

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
