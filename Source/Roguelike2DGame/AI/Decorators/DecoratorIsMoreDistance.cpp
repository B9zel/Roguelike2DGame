// Fill out your copyright notice in the Description page of Project Settings.


#include "DecoratorIsMoreDistance.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>



UDecoratorIsMoreDistance::UDecoratorIsMoreDistance()
{
	Target.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UDecoratorIsMoreDistance, Target), AActor::StaticClass());
}

bool UDecoratorIsMoreDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (!Target.IsSet())
	{
		return false;
	}
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));
	if (!target)
	{
		return false;
	}
	UE_LOG(LogTemp, Display, TEXT("%s"), *(OwnerComp.GetOwner()->GetActorLocation() - target->GetActorLocation()).ToString());
	UE_LOG(LogTemp, Display, TEXT("Target %s"), *(target->GetActorLocation()).ToString());
	UE_LOG(LogTemp, Display, TEXT("Owner %s"), *(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()).ToString());
	return (target->GetActorLocation() - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()).Length() > Distance;
}
