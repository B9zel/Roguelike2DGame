// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeKingAIController.h"
#include "../../../../Characters/Enemies/MeleeEnemies/Bosses/SlimeKing/SlimeKing.h"
#include "../../../../Data/Enums/EBossStage.h"

#include <BehaviorTree/BlackboardComponent.h>




void ASlimeKingAIController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);

	ASlimeKing* ControlledPawn = Cast<ASlimeKing>(newPawn);

	if (ControlledPawn)
	{
		ControlledPawn->switchStage.AddDynamic(this, &ASlimeKingAIController::OnSwitchStage);
	}
}

void ASlimeKingAIController::OnSwitchStage(const EBossStage& newStage)
{
	GetBlackboardComponent()->SetValueAsEnum(NameOfEnumStage, static_cast<uint8>(newStage));
}
