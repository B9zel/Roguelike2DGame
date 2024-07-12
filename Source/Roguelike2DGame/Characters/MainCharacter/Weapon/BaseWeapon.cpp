// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "../../BasePaperCharacter.h"
#include "../../../Data/Enums/EWeaponType.h"

#include <Kismet/KismetMathLibrary.h>

UBaseWeapon::UBaseWeapon()
{
	isAttacking = false;
	canAttack = true;

	damage = 1.f;
	timeReload = 5;
}

void UBaseWeapon::PostInitProperties()
{
	Super::PostInitProperties();

	if (GetWorld())
	{
		owner = Cast<ABasePaperCharacter>(GetOuter());
	}
}

void UBaseWeapon::StartReload()
{
	if (!reloadHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(reloadHandle, this, &UBaseWeapon::FinishReload, timeReload, false);
	}
}

void UBaseWeapon::SetTimeReload(float time)
{
	if (time < 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Negative value can't set"));
		return;
	}
	timeReload = time;
}

void UBaseWeapon::FinishReload()
{
	SetIsAttacking(false);
	SetCanAttack(true);
	reloadHandle.Invalidate();
}
