// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskChooseNextStroke.h"
#include <Kismet/KismetMathLibrary.h>
#include <BehaviorTree/BlackboardComponent.h>



UTaskChooseNextStroke::UTaskChooseNextStroke()
{
	VarBool.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UTaskChooseNextStroke, VarBool));
}

EBTNodeResult::Type UTaskChooseNextStroke::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(VarBool.SelectedKeyName, UKismetMathLibrary::RandomBoolWithWeight(ProbabilityOfTrue));

	return EBTNodeResult::Succeeded;
}
