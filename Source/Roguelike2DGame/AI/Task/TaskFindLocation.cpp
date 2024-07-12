// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskFindLocation.h"
#include "../../Controllers/Game/AI/Melee/BaseMeleeAIController.h"
#include "../../Characters/Enemies/EnemyCharacter.h"
#include "../../Components/Stat/CharacterStatsComponent.h"

#include <Kismet/KismetSystemLibrary.h>
#include <BehaviorTree/BlackboardComponent.h>


EBTNodeResult::Type UTaskFindLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	
	ABaseMeleeAIController* ownerController = Cast<ABaseMeleeAIController>(OwnerComp.GetAIOwner());

	if (ownerController != nullptr)
	{
		FVector startLocation = ownerController->GetPawn()->GetActorLocation();
		FVector endLocation = ownerController->GetPawn()->GetActorForwardVector() * ownerController->GetDistancePatrolling();
		TArray<AActor*> ignoreActors = { ownerController->GetPawn()};
		TArray<FHitResult> res;

		UKismetSystemLibrary::LineTraceMultiForObjects(ownerController->GetPawn(), startLocation, startLocation + endLocation, ownerController->GetPawn<AEnemyCharacter>()->GetTargetEnumsObject(), true, ignoreActors, EDrawDebugTrace::ForDuration,res, true);
		
		UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
		if (!res.IsEmpty())
		{
			Blackboard->SetValueAsVector(locationProperty.SelectedKeyName, res.GetData()->Location);
		}
		else
		{
			Blackboard->SetValueAsVector(locationProperty.SelectedKeyName, startLocation + endLocation);
		}
		

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}