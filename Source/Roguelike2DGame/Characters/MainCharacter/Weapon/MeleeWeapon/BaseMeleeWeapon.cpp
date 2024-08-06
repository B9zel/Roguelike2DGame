// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseMeleeWeapon.h"



void UBaseMeleeWeapon::StartReload_Implementation()
{
	if (timeReload == 0.f)
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
