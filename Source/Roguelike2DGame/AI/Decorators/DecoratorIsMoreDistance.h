// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "DecoratorIsMoreDistance.generated.h"

/**
 *  
 */
UCLASS()
class ROGUELIKE2DGAME_API UDecoratorIsMoreDistance : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()
	
public:

	UDecoratorIsMoreDistance();

public:

	// @return true if distance between owning actor and "Target" more "Distance", else false;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Target;
	UPROPERTY(EditAnywhere)
	float Distance;

};
