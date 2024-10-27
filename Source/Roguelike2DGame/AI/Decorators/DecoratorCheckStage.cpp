// Fill out your copyright notice in the Description page of Project Settings.


#include "DecoratorCheckStage.h"
#include <BehaviorTree/BlackboardComponent.h>






bool UDecoratorCheckStage::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (typeCompare == ECompare::EQUAL)
	{
		return OwnerComp.GetBlackboardComponent()->GetValueAsEnum(enumVar.SelectedKeyName) == static_cast<uint8>(Compared);
	}
	
	
	return OwnerComp.GetBlackboardComponent()->GetValueAsEnum(enumVar.SelectedKeyName) != static_cast<uint8>(Compared);
}