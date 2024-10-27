// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include <Navigation/PathFollowingComponent.h>
#include "TaskStepBack.generated.h"


struct FAIRequestID;
class ACharacter;

UCLASS()
class ROGUELIKE2DGAME_API UTaskStepBack : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UFUNCTION()
	void FinishMove(EPathFollowingResult::Type MovementResult);

protected:

	UPROPERTY(EditAnywhere, meta=(ClampMin="0"))
	float SpeedRetreat;

	UPROPERTY(EditAnywhere, meta=(ClampMin="0"))
	float Distance;

private:

	AAIController* OwningController;
	ACharacter* Owner;
	float DefaultSpeed;

};
