// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"
#include <PaperZDAnimationComponent.h>
#include <PaperZDAnimInstance.h>
#include <Kismet/GameplayStatics.h>





void AMeleeEnemy::OnAttack()
{
	canAttack = false;
	isAttacking = true;
}

void AMeleeEnemy::OnAttackHit()
{
	TArray<AActor*> actorsIgnore;
	TArray<FHitResult> res;
	TSubclassOf<UDamageType> damageType;
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * distanceAttack), 15, 35, targetEnums, false, actorsIgnore, EDrawDebugTrace::ForDuration, res, true);

	for (auto& el : res)
	{
		UGameplayStatics::ApplyDamage(el.GetActor(), damage, GetInstigatorController(), this, damageType);
	}

	GetWorld()->GetTimerManager().SetTimer(attackReloadTimer, this, &AMeleeEnemy::OnReloadAttack, timeReloadAttack, false);
}

