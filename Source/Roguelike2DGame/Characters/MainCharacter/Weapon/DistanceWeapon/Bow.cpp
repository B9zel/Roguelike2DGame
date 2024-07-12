// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"
#include "../../../../Data/Enums/EWeaponType.h"


UBow::UBow()
{
	weaponType = EWeaponType::BOW;
}

void UBow::StartAttack_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Bow attack"));
}
