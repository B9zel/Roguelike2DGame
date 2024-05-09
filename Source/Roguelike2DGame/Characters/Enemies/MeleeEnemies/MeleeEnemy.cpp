// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"
#include <PaperZDAnimationComponent.h>
#include <PaperZDAnimInstance.h>
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>
#include <GameFramework/CharacterMovementComponent.h>





AMeleeEnemy::AMeleeEnemy()
{
	collisonBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	collisonBoxComponent->SetupAttachment(GetRootComponent());

	timeStayInPatrolling = 1.f;
}

float AMeleeEnemy::GetTimeStayPatrolling()
{
	return timeStayInPatrolling;
}


void AMeleeEnemy::OnAttack()
{
	canAttack = false;
	isAttacking = true;
	GetCharacterMovement()->SetActive(false);
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

	GetCharacterMovement()->SetActive(true);
	GetWorld()->GetTimerManager().SetTimer(attackReloadTimer, this, &AMeleeEnemy::OnReloadAttack, timeReloadAttack, false);
}

