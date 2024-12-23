// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

void ABaseAIController::JumpSetup()
{
	ACharacter* owningCharacter = GetCharacter();
	if (!owningCharacter) return;

	defaultGravityScale = owningCharacter->GetCharacterMovement()->GravityScale;
	owningCharacter->GetCharacterMovement()->GravityScale = gravityJump;
}

void ABaseAIController::StopJumpSetup()
{
	ACharacter* owningCharacter = GetCharacter();
	if (!owningCharacter) return;

	owningCharacter->GetCharacterMovement()->GravityScale = defaultGravityScale;
}