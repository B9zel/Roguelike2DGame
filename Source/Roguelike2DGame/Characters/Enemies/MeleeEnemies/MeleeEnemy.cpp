// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"
#include <PaperZDAnimationComponent.h>
#include <PaperZDAnimInstance.h>
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>





AMeleeEnemy::AMeleeEnemy(const FObjectInitializer& OI) : Super(OI)
{
	collisonBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	collisonBoxComponent->SetupAttachment(GetRootComponent());
}

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
	if (UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * distanceAttack), 15, 35, targetEnums, false, actorsIgnore, EDrawDebugTrace::ForDuration, res, true))
	{
		for (auto& el : res)
		{
			UGameplayStatics::ApplyDamage(el.GetActor(), damage, GetInstigatorController(), this, damageType);
		}
	}
}

void AMeleeEnemy::OnEndAttack()
{
	Super::OnEndAttack();

	GetWorld()->GetTimerManager().SetTimer(attackReloadTimer, this, &AMeleeEnemy::OnReloadAttack, timeReloadAttack, false);
}

