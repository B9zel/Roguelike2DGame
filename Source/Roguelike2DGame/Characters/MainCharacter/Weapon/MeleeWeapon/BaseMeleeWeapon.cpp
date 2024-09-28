// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMeleeWeapon.h"
#include "../../../BasePaperCharacter.h"

#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>



void UBaseMeleeWeapon::Attack_Implementation()
{
	SetIsReady(false);

	const TArray<AActor*> actorsIgnore;
	TArray<FHitResult> res;
	TSubclassOf<UDamageType> damageType;

	const FVector actorLocation = GetOwner()->GetActorLocation();
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, actorLocation, actorLocation + (GetOwner()->GetActorForwardVector() * GetDistanceAttack()),
		capsuleRadiusAttack, capsuleHalfHeightAttack, typesAttackCollision, false, actorsIgnore, EDrawDebugTrace::ForDuration, res, true);

	for (auto& el : res)
	{
		UGameplayStatics::ApplyDamage(el.GetActor(), GetDamage(), GetOwner()->GetInstigatorController(), GetOwner(), damageType);
	}
}

void UBaseMeleeWeapon::StartReload_Implementation()
{
	if (timeReload <= 0.0f)
	{
		FinishReload();
	}
	else if (!reloadHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(reloadHandle, this, &UBaseMeleeWeapon::FinishReload, timeReload, false);
	}
}


void UBaseMeleeWeapon::SetTimeReload(const float time)
{
	CHECK_WITH_LOG_WARNING(time < 0.0f, "Negative value can't set")

	timeReload = time;
}

float UBaseMeleeWeapon::GetTimeReload()
{
	return timeReload;
}

void UBaseMeleeWeapon::SetDistanceAttack(float distance)
{
	distanceOfAttack = distance < 0.0f ? 0.0f : distance;
}

void UBaseMeleeWeapon::OnEndAnimationAttack()
{
	Super::OnEndAnimationAttack();

	SetIsAttacking(false);
}