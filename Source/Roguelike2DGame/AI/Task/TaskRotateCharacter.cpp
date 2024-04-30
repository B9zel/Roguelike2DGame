// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskRotateCharacter.h"
#include <AIController.h>


EBTNodeResult::Type UTaskRotateCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (pawn != nullptr)
	{
		pawn->AddActorWorldRotation(FRotator(0, 180, 0));
		return EBTNodeResult::Succeeded;
	}

	
	return EBTNodeResult::Failed;
}
