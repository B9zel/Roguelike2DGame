// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "TaskChooseNextStroke.generated.h"



UCLASS()
class ROGUELIKE2DGAME_API UTaskChooseNextStroke : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:

	UTaskChooseNextStroke();


public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector VarBool;

	UPROPERTY(EditAnywhere, meta=(ClampMin="0.0", ClampMax="1.0"))
	float ProbabilityOfTrue;
};
