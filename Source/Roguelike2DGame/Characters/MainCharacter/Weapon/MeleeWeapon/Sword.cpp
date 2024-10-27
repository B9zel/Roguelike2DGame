// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "../../../../Data/Enums/EWeaponType.h"
#include "../../../BasePaperCharacter.h"

#include <GameFramework/CharacterMovementComponent.h>



USword::USword()
{
	weaponType				= EWeaponType::SWORD;
	damage					= 1;
	distanceOfAttack		= 20;
	capsuleRadiusAttack		= 15;
	capsuleHalfHeightAttack = 25;
	timeReload				= 0.5f;
	m_CanUseSecondAttack	= false;
}



void USword::PostInitProperties()
{
	Super::PostInitProperties();

	if (GetWorld())
	{
		GetOwner()->LandedDelegate.AddDynamic(this, &USword::OnLendedOwnerCharacter);
	}
}

void USword::StartAttack()
{
	if (m_CanUseSecondAttack && m_TimeBetweenAttackHandle.IsValid() || GetCanAttack())
	{
		SetCanAttack(true);
		Super::StartAttack();

		if (GetOwner()->GetCharacterMovement()->IsWalking())
		{
			GetOwner()->DisableCharacterMovement();
		}
	}
}

void USword::Attack_Implementation()
{
	Super::Attack_Implementation();

	GetWorld()->GetTimerManager().SetTimer(m_TimeBetweenAttackHandle, this, &USword::ResetAttackAnim, TimeAttackCombo);
}

void USword::StartAnimAttack()
{
	if (m_CanUseSecondAttack)
	{
		GetOwner()->PlayAnimation(SecondAttackAnimation);
		m_CanUseSecondAttack = false;
	}
	else
	{
		GetOwner()->PlayAnimation(AttackAnimation);
		m_CanUseSecondAttack = true;
	}
}

void USword::OnEndAnimationAttack()
{
	Super::OnEndAnimationAttack();

	GetOwner()->EnableCharacterMovement();
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

void USword::ResetAttackAnim()
{
	m_CanUseSecondAttack = false;
	m_TimeBetweenAttackHandle.Invalidate();
}

void USword::OnLendedOwnerCharacter(const FHitResult& Hit)
{
	if (IsAttacking())
	{
		GetOwner()->DisableCharacterMovement();
	}
}
