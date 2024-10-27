// Fill out your copyright notice in the Description page of Project Settings.


#include "Scythe.h"
#include "../../../../Characters/BasePaperCharacter.h"
#include "../../../../Data/Enums/EWeaponType.h"

#include <GameFramework/CharacterMovementComponent.h>



UScythe::UScythe()
{
	weaponType = EWeaponType::SCYTHE;
	damage = 1;
	distanceOfAttack = 20;
	capsuleRadiusAttack = 15;
	capsuleHalfHeightAttack = 25;
	timeReload = 0.5f;
}



void UScythe::PostInitProperties()
{
	Super::PostInitProperties();

	if (GetWorld())
	{
		GetOwner()->LandedDelegate.AddDynamic(this, &UScythe::OnLendedOwnerCharacter);
	}
}

bool UScythe::DamageLevelUp()
{
	if (Super::DamageLevelUp())
	{
		SetDamage(GetDamage() + levelUpDamage);
		return true;
	}
	return false;
}

bool UScythe::SpeedAttackLevelUp()
{
	if (Super::SpeedAttackLevelUp())
	{
		SetTimeReload(GetTimeReload() - levelUpTimeReload);
		return true;
	}
	return false;
}

void UScythe::StartAttack()
{
	if (!GetCanAttack()) return;

	Super::StartAttack();

	if (!GetOwner()->GetCharacterMovement()->IsFalling())
	{
		GetOwner()->DisableCharacterMovement();
	}
}

void UScythe::OnEndAnimationAttack()
{
	Super::OnEndAnimationAttack();

	GetOwner()->EnableCharacterMovement();
}


void UScythe::OnLendedOwnerCharacter(const FHitResult& Hit)
{
	if (IsAttacking())
	{
		GetOwner()->DisableCharacterMovement();
	}
}
