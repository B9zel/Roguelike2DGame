// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "../../../../Components/HealthManaComponent/ManaComponent.h"
#include "../../../MainCharacter/MainPaperCharacter.h"
#include "../../../BasePaperCharacter.h"
#include "../../../../Data/Enums/EWeaponType.h"
#include "Projectiles/Arrow.h"

#include <GameFramework/CharacterMovementComponent.h>




UBow::UBow()
{
	weaponType = EWeaponType::BOW;
	costOfUse = 0;
	isReady = false;
}

void UBow::PostInitProperties()
{
	Super::PostInitProperties();

	if (GetWorld())
	{
		owningPleryCharacter = Cast<AMainPaperCharacter>(GetOwner());
	}
}

void UBow::StartAttack()
{
	check(owningPleryCharacter);

	UManaComponent* Mana = owningPleryCharacter->GetManaComponent();

	if (!Mana || Mana->GetMana() < costOfUse) return;

	if (GetOwner()->GetCharacterMovement()->IsWalking())
	{
		Super::StartAttack();
		GetOwner()->DisableCharacterMovement();
	}

	SetIsReady(false);
}

void UBow::StopAttack_Implementation()
{
	SetIsAttacking(false);
	SetCanAttack(true);
	GetOwner()->EnableCharacterMovement();

	if (!IsReady() || GetOwner()->GetCharacterMovement()->IsFalling()) return;


	UManaComponent* Mana = owningPleryCharacter->GetManaComponent();

	check(Mana);
	Mana->SetMana(Mana->GetMana() - costOfUse);


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
