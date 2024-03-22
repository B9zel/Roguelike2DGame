// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>


AEnemyCharacter::AEnemyCharacter()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	Tags.Add("Enemy");
}



TArray<TEnumAsByte<EObjectTypeQuery>> AEnemyCharacter::GetBlockObjectPatrolling()
{
	return blockObjectPatrolling;
}

void AEnemyCharacter::SwitchDirectionX()
{
	if (GetActorForwardVector().X < 0)
	{
		SetActorRotation(FRotator(0.f, 0.f, 0.f));
	}
	else
	{
		SetActorRotation(FRotator(0.f, 180.f, 0.f));
	}
}
