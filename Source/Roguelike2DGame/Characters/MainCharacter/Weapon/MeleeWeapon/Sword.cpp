// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "../../../../Data/Enums/EWeaponType.h"




USword::USword()
{
	weaponType = EWeaponType::SWORD;
	damage = 1;
	distanceOfAttack = 20;
	capsuleRadiusAttack = 15;
	capsuleHalfHeightAttack = 25;
	timeReload = 0.5f;
}

bool USword::DamageLevelUp()
{
	if (Super::DamageLevelUp())
	{
		SetDamage(GetDamage() + levelUpDamage);
		return true;
	}
	return false;
}

bool USword::SpeedAttackLevelUp()
{
	if (Super::SpeedAttackLevelUp())
	{
		SetTimeReload(GetTimeReload() - levelUpTimeReload);
		return true;
	}
	return false;
}