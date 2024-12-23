// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"
#include "../../../Components/Stat/CharacterStatsComponent.h"


#include <GameFramework/CharacterMovementComponent.h>
#include <PaperZDAnimationComponent.h>
#include <PaperZDAnimInstance.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>





AMeleeEnemy::AMeleeEnemy()
{
	//collisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	//collisionBoxComponent->SetupAttachment(GetRootComponent());

	timeStayInPatrolling = 1.0f;
	timeReloadAttack = 1.0f;
	canAttack = true;
	isAttacking = false;
}

float AMeleeEnemy::GetTimeStayPatrolling()
{
	return timeStayInPatrolling;
}

void AMeleeEnemy::OnAttack()
{
	SetCanAttack(false);
	SetIsAttacking(true);
	GetCharacterMovement()->SetActive(false);
}

void AMeleeEnemy::OnAttackHit()
{
	Super::OnAttackHit();

	TArray<AActor*> actorsIgnore;
	TArray<FHitResult> res;
	TSubclassOf<UDamageType> damageType;
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * GetDistanceAttack()),
		capsuleRadiusAttack, capsuleHalfHeightAttack, GetTypesAttackCollision(), false, actorsIgnore, EDrawDebugTrace::ForDuration, res, true);
	
	for (auto& el : res)
	{
		UGameplayStatics::ApplyDamage(el.GetActor(), GetDamage(), GetInstigatorController(), this, damageType);
	}
}

void AMeleeEnemy::OnEndAnimAttack()
{
	Super::OnEndAnimAttack();

	SetIsAttacking(false);
	GetCharacterMovement()->SetActive(true);
	GetWorld()->GetTimerManager().SetTimer(attackReloadTimer, this, &AMeleeEnemy::OnReloadAttack, GetTimeReloadAttack(), false);
}

void AMeleeEnemy::OnReloadAttack()
{
	Super::OnReloadAttack();

	SetCanAttack(true);
}

void AMeleeEnemy::SetTimeReloadAttack(float time)
{
	timeReloadAttack = time < 0.0f ? 0.0f : time;
}