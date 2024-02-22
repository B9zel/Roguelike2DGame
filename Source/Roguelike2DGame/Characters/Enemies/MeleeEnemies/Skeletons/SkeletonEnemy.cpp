// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonEnemy.h"
#include <PaperZDAnimInstance.h>




ASkeletonEnemy::ASkeletonEnemy(const FObjectInitializer& OI) : Super(OI)
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
	if (deadActor == this)
	{
		GetAnimInstance()->JumpToNode("Death");
		DisableInput(GetController<APlayerController>());

		FTimerHandle timer;
		GetWorld()->GetTimerManager().SetTimer(timer, this, &ASkeletonEnemy::Destroyer, 3, false);
	}
}

void ASkeletonEnemy::OnTakePlayerDamage(AActor* instigatorDamage)
{
	Super::OnTakePlayerDamage(instigatorDamage);

	UE_LOG(LogTemp, Warning, TEXT("Damage"));
	if (!isAttacking)
	{
		GetAnimInstance()->JumpToNode("TakeDamage");
	}
}

void ASkeletonEnemy::Destroyer()
{
	Destroy();
}


