// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>
#include "../../Interact/BaseInteraction.h"


AEnemyCharacter::AEnemyCharacter()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	Tags.Add("Enemy");

	countDropMoney = 5;
}




void AEnemyCharacter::OnDeath(AActor* deadActor)
{
	Super::OnDeath(deadActor);

	if (deadActor != this)
		return;

	ABaseInteraction* act = nullptr;
	for (size_t i = 0; i < countDropMoney; i++)
	{
		act = GetWorld()->SpawnActor<ABaseInteraction>(moneyInteract, GetActorLocation(), GetActorRotation());
	}



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

//TArray<TEnumAsByte<EObjectTypeQuery>> AEnemyCharacter::GetBlockObjectPatrolling()
//{
//	return blockObjectPatrolling;
//}