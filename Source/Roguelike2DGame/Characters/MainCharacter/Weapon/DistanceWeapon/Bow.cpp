// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "../../../../Data/Enums/EWeaponType.h"
#include "Projectiles/Arrow.h"
#include "../../../BasePaperCharacter.h"


UBow::UBow()
{
	weaponType = EWeaponType::BOW;
	isReady = false;
}

void UBow::StartAttack_Implementation()
{
	SetIsReady(false);
}

void UBow::StopAttack_Implementation()
{
	SetIsAttacking(false);
	if (!IsReady())
	{
		return;
	}
	FActorSpawnParameters spawnParam;
	spawnParam.Instigator = GetOwner();
	spawnParam.Owner = nullptr;

	AArrow* arrow = GetWorld()->SpawnActor<AArrow>(projectileClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), spawnParam);
	arrow->SetDamage(damage);
}

bool UBow::DamageLevelUp()
{
	if (Super::DamageLevelUp())
	{
		SetDamage(GetDamage() + levelUpDamage);
		return true;
	}
	return false;
}

bool UBow::SpeedAttackLevelUp()
{
	if (Super::SpeedAttackLevelUp())
	{
		SetTimeReload(GetTimeReload() + levelUpRateReload);
		return true;
	}
	return false;
}