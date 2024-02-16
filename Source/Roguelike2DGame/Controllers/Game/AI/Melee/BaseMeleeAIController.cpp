// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMeleeAIController.h"
#include <GameFramework/Character.h>
#include "../../../../Characters/Enemies/MeleeEnemies/MeleeEnemy.h"

ABaseMeleeAIController::ABaseMeleeAIController()
{
	isAttackMode = false;
	isPatrollingMode = true;
	distanceVisionOfPatrolling = 100.f;
	timeStay = 2.f;
	toAttackCharacter = nullptr;
	controlledCharacter = nullptr;
}

const AMeleeEnemy* ABaseMeleeAIController::GetControlledCharacter()
{
	return controlledCharacter;
}

const ACharacter* ABaseMeleeAIController::GetToAttackCharacter()
{
	return toAttackCharacter;
}

void ABaseMeleeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	controlledCharacter = Cast<AMeleeEnemy>(InPawn);

	controlledCharacter->reloadAttack.AddDynamic(this, &ABaseMeleeAIController::OnRealoadAttackCharacter);
}

void ABaseMeleeAIController::OnRealoadAttackCharacter()
{
	if (isAttackMode)
	{
		OnAttckCharacter();
	}
}
