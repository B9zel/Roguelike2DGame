// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskRotateCharacter.h"
#include <AIController.h>


EBTNodeResult::Type UTaskRotateCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (pawn != nullptr)
	{
		FRotator pawnRotator = pawn->GetActorRotation();
		if (pawnRotator.Yaw > 0)
		{
			pawnRotator.Yaw = 0;
			pawn->SetActorRotation(pawnRotator);
		}
		else
		{
			pawnRotator.Yaw = 180;
			pawn->SetActorRotation(pawnRotator);
		}
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}
