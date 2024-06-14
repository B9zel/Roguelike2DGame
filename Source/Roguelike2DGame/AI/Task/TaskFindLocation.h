// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "TaskFindLocation.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API UTaskFindLocation : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector locationProperty;
};
