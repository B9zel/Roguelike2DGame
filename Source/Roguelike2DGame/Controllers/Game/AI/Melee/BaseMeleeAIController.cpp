// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMeleeAIController.h"
#include <GameFramework/Character.h>
#include <Perception/AIPerceptionComponent.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Navigation/PathFollowingComponent.h>
#include <Kismet/GameplayStatics.h>
#include "../../../../GameModes/Game/MainGameMode.h"
#include "../../../../Characters/Enemies/MeleeEnemies/MeleeEnemy.h"


ABaseMeleeAIController::ABaseMeleeAIController()
{
	perceptionAIComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception component"));
	
	isPatrollingMode = true;

	timeStay = 2.f;

	controlledCharacter = nullptr;
	actorToAttack = nullptr;
}

//const AMeleeEnemy* ABaseMeleeAIController::GetControlledCharacter()
//{
//	return controlledCharacter;
//}
//
FVector ABaseMeleeAIController::GetDistancePatrolling()
{
	return distancePatrolling;
}

void ABaseMeleeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	controlledCharacter = Cast<AMeleeEnemy>(InPawn);
	if (controlledCharacter)
	{
	//	controlledCharacter->reloadAttack.AddDynamic(this, &ABaseMeleeAIController::OnRealoadAttackCharacter);
	}
	if (auto* mode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		mode->deathDeligate.AddDynamic(this, &ABaseMeleeAIController::OnDeathControlledCharacter);
	}

	perceptionAIComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseMeleeAIController::OnTargetPerceptionUpdate);

}



void ABaseMeleeAIController::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
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
			actorToAttack = nullptr;
		}

		GetBlackboardComponent()->SetValueAsObject(actorToAttackKey, actorToAttack);
	}
}

//
//void ABaseMeleeAIController::OnRealoadAttackCharacter()
//{
//	OnAttckCharacter();
//}

void ABaseMeleeAIController::OnDeathControlledCharacter(AActor* actor, AActor* InstigatorActor)
{
	if (actor == GetPawn())
	{
		UnPossess();
		Destroy();
	}
}
