// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonKingAIController.h"
#include "../../../../Characters/Enemies/MeleeEnemies/Bosses/SkeletonKing/SkeletonKing.h"

#include <GameFramework/CharacterMovementComponent.h>



ASkeletonKingAIController::ASkeletonKingAIController()
{
	defaultGravityScale = 1.0f;
}

void ASkeletonKingAIController::JumpSetup()
{
	defaultGravityScale = owningCharacter->GetCharacterMovement()->GravityScale;
	owningCharacter->GetCharacterMovement()->GravityScale = gravityJump;
}

void ASkeletonKingAIController::StopJumpSetup()
{
	owningCharacter->GetCharacterMovement()->GravityScale = defaultGravityScale;
}

void ASkeletonKingAIController::OnPossess(APawn* PawnTo)
{
	Super::OnPossess(PawnTo);

	owningCharacter = Cast<ASkeletonKing>(GetPawn());
}
