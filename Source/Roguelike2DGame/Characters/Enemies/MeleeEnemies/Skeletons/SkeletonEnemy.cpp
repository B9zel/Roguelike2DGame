// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonEnemy.h"
#include <PaperZDAnimInstance.h>
#include "../../../../Components/HealthManaComponent/HealthManaComponent.h"



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
	if (canAttack)
	{
		AMeleeEnemy::OnAttack();

		GetAnimInstance()->JumpToNode(anim.attack);
	}
}

void ASkeletonEnemy::OnReloadAttack()
{
	Super::OnReloadAttack();

}

void ASkeletonEnemy::OnDeath(AActor* deadActor)
{
	Super::OnDeath(deadActor);
	if (deadActor == this)
	{
		GetAnimInstance()->JumpToNode(anim.death);
		DisableInput(GetController<APlayerController>());
		

		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, this, &ASkeletonEnemy::Destroyer, timeDestroyAfterDeath, false);
	}
}

void ASkeletonEnemy::OnTakePlayerDamage(AActor* instigatorDamage)
{
	Super::OnTakePlayerDamage(instigatorDamage);

	//UE_LOG(LogTemp, Warning, TEXT("Damage"));
	if (!isAttacking && !healthComponent->GetIsDead())
	{
		GetAnimInstance()->JumpToNode(anim.takeDamage);
	}
}

void ASkeletonEnemy::Destroyer()
{
	Destroy();
}


