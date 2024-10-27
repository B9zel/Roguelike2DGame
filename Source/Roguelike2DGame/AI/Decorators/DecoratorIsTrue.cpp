// Fill out your copyright notice in the Description page of Project Settings.


#include "DecoratorIsTrue.h"
#include <BehaviorTree/BlackboardComponent.h>


UDecoratorIsTrue::UDecoratorIsTrue()
{
	CheckKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UDecoratorIsTrue, CheckKey));
}

bool UDecoratorIsTrue::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(CheckKey.SelectedKeyName) ==  (Check == EBoolType::SET_TRUE ? true : false);
}
