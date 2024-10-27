// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "../../Data/Enums/EBossStage.h"
#include "DecoratorCheckStage.generated.h"




UENUM(BlueprintType)
enum class ECompare : uint8
{
	EQUAL = 0,
	NOT_EQUAL
};


UCLASS()
class ROGUELIKE2DGAME_API UDecoratorCheckStage : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()

public:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector enumVar;

	UPROPERTY(EditAnywhere)
	EBossStage Compared;

	UPROPERTY(EditAnywhere)
	ECompare typeCompare;
};
