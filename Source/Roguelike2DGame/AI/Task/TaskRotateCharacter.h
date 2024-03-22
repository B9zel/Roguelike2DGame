// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "TaskRotateCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API UTaskRotateCharacter : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

protected:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
