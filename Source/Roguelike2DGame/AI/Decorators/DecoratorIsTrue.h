// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "DecoratorIsTrue.generated.h"


UENUM(BlueprintType)
enum class EBoolType : uint8
{
	SET_TRUE = 0,
	SET_FALSE
};


UCLASS()
class ROGUELIKE2DGAME_API UDecoratorIsTrue : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()
	
public:

	UDecoratorIsTrue();

public:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CheckKey;

	UPROPERTY(EditAnywhere)
	EBoolType Check;
};
