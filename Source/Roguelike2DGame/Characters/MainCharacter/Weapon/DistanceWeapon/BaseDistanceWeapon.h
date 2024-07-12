// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseWeapon.h"
#include "../../../../Interfaces/Weapon/DistanceWeapon.h"
#include "BaseDistanceWeapon.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class ROGUELIKE2DGAME_API UBaseDistanceWeapon : public UBaseWeapon, public IDistanceWeapon
{
	GENERATED_BODY()
	
public:

	UBaseDistanceWeapon();

	
protected:

};
