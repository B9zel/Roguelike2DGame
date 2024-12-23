// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskAttackAndSpawnDuringHit.h"
#include "../../Characters/Enemies/EnemyCharacter.h"

#include <AIController.h>


EBTNodeResult::Type UTaskAttackAndSpawnDuringHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwningCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!OwningCharacter) return EBTNodeResult::Failed;

	if (!OwningCharacter->endAnimAttack.Contains(this, "EndAttack"))
	{
		OwningCharacter->endAnimAttack.AddDynamic(this, &UTaskAttackAndSpawnDuringHit::EndAttack);
	}
	if (!OwningCharacter->hitAttack.Contains(this, "HitAttack"))
	{
		OwningCharacter->hitAttack.AddDynamic(this, &UTaskAttackAndSpawnDuringHit::HitAttack);
	}
	OwningCharacter->OnAttack();


	return EBTNodeResult::InProgress;
}

void UTaskAttackAndSpawnDuringHit::EndAttack()
{
	FinishExecute(true);
}

void UTaskAttackAndSpawnDuringHit::HitAttack()
{
	if (OwningCharacter && Spawn.Get())
	{
		FActorSpawnParameters paramSpawn;
		paramSpawn.Owner = OwningCharacter;
		GetWorld()->SpawnActor<AActor>(Spawn, FTransform(OwningCharacter->GetActorTransform()), paramSpawn);
	}
}
