// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeEnemy.h"
#include "../../../../Components/HealthManaComponent/HealthComponent.h"

#include <GameFramework/CharacterMovementComponent.h>





void ASlimeEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void ASlimeEnemy::OnAttack()
{
	if (GetCanAttack())
	{
		Super::OnAttack();
		PlayAnimation(Animations.attack);
	}
}

void ASlimeEnemy::OnDeath_Implementation(AActor* deadActor, AActor* InstigatorActor)
{
	Super::OnDeath_Implementation(deadActor, InstigatorActor);
	if (deadActor == this)
	{
		PlayAnimation(Animations.death);
	}
}

float ASlimeEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!IsAttacking() && !healthComponent->GetIsDead())
	{
		PlayAnimation(Animations.takeDamage);
	}
	return DamageAmount;
}

float ASlimeEnemy::GetRunSpeed()
{
	return runSpeed;
}

float ASlimeEnemy::GetWalkSpeed()
{
	return walkSpeed;
}