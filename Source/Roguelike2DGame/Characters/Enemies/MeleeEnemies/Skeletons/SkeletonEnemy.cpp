// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonEnemy.h"
#include "../../../../Components/HealthManaComponent/HealthComponent.h"
#include "../../../../Components/Stat/CharacterStatsComponent.h"

#include <PaperZDAnimInstance.h>




ASkeletonEnemy::ASkeletonEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASkeletonEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void ASkeletonEnemy::Tick(float deltaTime)
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

void ASkeletonEnemy::OnAttack()
{
	if (GetCanAttack())
	{
		AMeleeEnemy::OnAttack();

		GetAnimInstance()->JumpToNode(anim.attack);
	}
}

void ASkeletonEnemy::OnReloadAttack()
{
	Super::OnReloadAttack();

}

void ASkeletonEnemy::OnDeath(AActor* deadActor, AActor* InstigatorActor)
{
	Super::OnDeath(deadActor, InstigatorActor);
	if (deadActor == this)
	{
		GetAnimInstance()->JumpToNode(anim.death);
		DisableInput(GetController<APlayerController>());
		

		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, this, &ASkeletonEnemy::Destroyer, timeDestroyAfterDeath, false);
	}
}

float ASkeletonEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!IsAttacking() && !healthComponent->GetIsDead())
	{
		GetAnimInstance()->JumpToNode(anim.takeDamage);
	}
	return DamageAmount;
}

void ASkeletonEnemy::Destroyer()
{
	Destroy();
}