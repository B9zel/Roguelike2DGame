// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "../../Interact/BaseInteraction.h"

#include <GameFramework/CharacterMovementComponent.h>




AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	countDropMoney = 5;
	countDropSouls = 1;
}

void AEnemyCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);


	if (GetVelocity().X > 0)
	{
		SetActorRotation(FRotator(0, 0, 0));
	}
	else if (GetVelocity().X < 0)
	{
		SetActorRotation(FRotator(0, 180, 0));
	}
}

void AEnemyCharacter::OnDeath_Implementation(AActor* deadActor, AActor* InstigatorActor)
{
	Super::OnDeath_Implementation(deadActor, InstigatorActor);

	if (deadActor == this)
	{
		for (size_t i = 0; i < countDropMoney; i++)
		{
			GetWorld()->SpawnActor<ABaseInteraction>(moneyInteract, GetActorLocation(), GetActorRotation());
		}

		DisableInput(GetController<APlayerController>());

		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, this, &AEnemyCharacter::Destroyer, timeDestroyAfterDeath, false);
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

void AEnemyCharacter::Destroyer()
{
	Destroy();
}