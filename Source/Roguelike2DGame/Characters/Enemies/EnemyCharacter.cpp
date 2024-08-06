// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "../../Interact/BaseInteraction.h"

#include <GameFramework/CharacterMovementComponent.h>


AEnemyCharacter::AEnemyCharacter()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	countDropMoney = 5;
	countDropSouls = 1;
}


void AEnemyCharacter::OnDeath(AActor* deadActor, AActor* InstigatorActor)
{
	Super::OnDeath(deadActor, InstigatorActor);

	if (deadActor != this)
		return;

	for (size_t i = 0; i < countDropMoney; i++)
	{
		GetWorld()->SpawnActor<ABaseInteraction>(moneyInteract, GetActorLocation(), GetActorRotation());
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


void AEnemyCharacter::SetDistanceAttack(float distance)
{
	distanceAttack = distance < 0.0f ? 0.0f : distance;
}

void AEnemyCharacter::SetDamage(int newDamage)
{
	damage = newDamage < 0 ? 0 : newDamage;
}