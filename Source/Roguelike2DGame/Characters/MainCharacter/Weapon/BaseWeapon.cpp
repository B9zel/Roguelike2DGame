// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "../../BasePaperCharacter.h"
#include "../../../Data/Enums/EWeaponType.h"
#include "../../../Data/DataAssets/LevelConfigDataAsset.h"

#include <Kismet/KismetMathLibrary.h>
#include <Engine/StreamableManager.h>




UBaseWeapon::UBaseWeapon()
{
	isAttacking = false;
	canAttack = true;

	damage = 1.f;
	currentLevelDamage = 1;
	currentLevelSpeedAttack = 1;
}

void UBaseWeapon::PostInitProperties()
{
	Super::PostInitProperties();
	
	if (GetWorld())
	{
		owner = Cast<ABasePaperCharacter>(GetOuter());
	}
}


bool UBaseWeapon::DamageLevelUp()
{
	if (GetLevelDamage() < GetMaxLevel())
	{
		SetSouls(GetSouls() - GetSoulsMaxForDamage());
		SetLevelDamage(GetLevelDamage() + 1);

		return true;
	}
	return false;
}

bool UBaseWeapon::SpeedAttackLevelUp()
{
	if (GetLevelSpeedAttack() < GetMaxLevel())
	{
		SetSouls(GetSouls() - GetSoulsMaxForAttackSpeed());
		SetLeveSpeedAttack(GetLevelSpeedAttack() + 1);

		return true;
	}
	return false;
}


void UBaseWeapon::FinishReload()
{
	SetCanAttack(true);
	SetIsReady(true);
	reloadHandle.Invalidate();
}

void UBaseWeapon::SetSouls(const int souls)
{
	CHECK_WITH_LOG_WARNING(souls < 0, "Can't set negative count \"souls\"")
	
	soulsCurrent = souls;
}

void UBaseWeapon::SetLevelDamage(const int level)
{
	CHECK_WITH_LOG_WARNING(level < 1, "Can't set negative count \"level\"")
	
	currentLevelDamage = level;
}

void UBaseWeapon::SetLeveSpeedAttack(const int level)
{
	CHECK_WITH_LOG_WARNING(level < 1, "Can't set negative count \"level\"")

	currentLevelSpeedAttack = level;
}

void UBaseWeapon::AddSouls(const int count)
{
	CHECK_WITH_LOG_WARNING(count < 0, "Can't add negative count \"souls\"")
	
	soulsCurrent += count;
}

int UBaseWeapon::GetMaxLevel() const
{
	return configLevel->maxLevel;
}

int UBaseWeapon::GetSoulsMaxForDamage() const
{
	return configLevel->levelSouls[GetLevelDamage()];
}

int UBaseWeapon::GetSoulsMaxForAttackSpeed() const
{
	return configLevel->levelSouls[GetLevelSpeedAttack()];
}

void UBaseWeapon::SetDamage(const int newDamage)
{
	damage = newDamage < 0 ? 0 : newDamage;
}
