// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonEnemy.h"
#include "../../../../Components/HealthManaComponent/HealthComponent.h"
#include "../../../../Components/Stat/CharacterStatsComponent.h"


#include <PaperZDAnimInstance.h>



ASkeletonEnemy::ASkeletonEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASkeletonEnemy::OnAttack()
{
	if (GetCanAttack())
	{
		AMeleeEnemy::OnAttack();

		PlayAnimation(anim.attack);
	}
}


void ASkeletonEnemy::OnDeath_Implementation(AActor* deadActor, AActor* InstigatorActor)
{
	Super::OnDeath(deadActor, InstigatorActor);
	if (deadActor == this)
	{
		PlayAnimation(anim.death);
	}
}

float ASkeletonEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!IsAttacking() && !healthComponent->GetIsDead())
	{
		PlayAnimation(anim.takeDamage);
	}
	return DamageAmount;
}

