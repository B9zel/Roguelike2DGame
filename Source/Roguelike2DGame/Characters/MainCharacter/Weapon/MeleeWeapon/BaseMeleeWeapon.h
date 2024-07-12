// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseWeapon.h"
#include "../../../../Interfaces/Weapon/MeleeWeapon.h"

#include "BaseMeleeWeapon.generated.h"



UCLASS(Abstract, Blueprintable)
class ROGUELIKE2DGAME_API UBaseMeleeWeapon : public UBaseWeapon, public IMeleeWeapon
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	float distanceOfAttack;
	
};
