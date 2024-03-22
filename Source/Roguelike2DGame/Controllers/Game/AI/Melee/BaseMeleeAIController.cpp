// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMeleeAIController.h"
#include <GameFramework/Character.h>
#include <Perception/AIPerceptionComponent.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Navigation/PathFollowingComponent.h>
#include "../../../../Characters/Enemies/MeleeEnemies/MeleeEnemy.h"


ABaseMeleeAIController::ABaseMeleeAIController()
{
	perceptionAIComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception component"));
	ReceiveMoveCompleted.AddDynamic(this, &ABaseMeleeAIController::OnMoveTo);

	isPatrollingMode = true;

	timeStay = 2.f;

	controlledCharacter = nullptr;
	actorToAttack = nullptr;
}

const AMeleeEnemy* ABaseMeleeAIController::GetControlledCharacter()
{
	return controlledCharacter;
}

FVector ABaseMeleeAIController::GetDistancePatrolling()
{
	return distancePatrolling;
}

void ABaseMeleeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	controlledCharacter = Cast<AMeleeEnemy>(InPawn);
	if (controlledCharacter != nullptr)
	{
		controlledCharacter->reloadAttack.AddDynamic(this, &ABaseMeleeAIController::OnRealoadAttackCharacter);
	}
	perceptionAIComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseMeleeAIController::OnTargetPerceptionUpdate);

}

void ABaseMeleeAIController::OnMoveTo(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Success)
	{
		
	}
}

void ABaseMeleeAIController::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Display, TEXT(" %s"),FString(Actor->GetFName().ToString()));
	//UE_LOG(LogTemp, Display, TEXT(" %s"), (Stimulus.WasSuccessfullySensed() ? TEXT("true") : TEXT("false")));
	if (Actor->ActorHasTag("PlayerCharacter"))
	{
		bool success = Stimulus.WasSuccessfullySensed();
		GetBlackboardComponent()->SetValueAsBool(isAttckKeyName, success);
		if (success)
		{
			actorToAttack = Actor;
		}
		else
		{
			FAIMoveRequest request;
			request.SetGoalLocation(Actor->GetActorLocation());
			MoveTo(request);
			
			actorToAttack = nullptr;
		}

		GetBlackboardComponent()->SetValueAsObject(actorToAttackKey, actorToAttack);
	}
}

void ABaseMeleeAIController::OnRealoadAttackCharacter()
{
	OnAttckCharacter();
}
