// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonEnemy.h"
#include <PaperZDAnimInstance.h>




void ASkeletonEnemy::OnAttack()
{
	if (canAttack)
	{
		AMeleeEnemy::OnAttack();

		GetAnimInstance()->JumpToNode("Attack");
	}
}

void ASkeletonEnemy::OnReloadAttack()
{
	Super::OnReloadAttack();

}

void ASkeletonEnemy::OnDeath(AActor* deadActor)
{
	Super::OnDeath(deadActor);

	GetAnimInstance()->JumpToNode("Death");
}

void ASkeletonEnemy::OnTakeDamage(AActor* instigatorDamage)
{
	Super::OnTakeDamage(instigatorDamage);

	UE_LOG(LogTemp, Warning, TEXT("Damage"));
	if (!isAttacking)
	{
		GetAnimInstance()->JumpToNode("TakeDamage");
	}
}


