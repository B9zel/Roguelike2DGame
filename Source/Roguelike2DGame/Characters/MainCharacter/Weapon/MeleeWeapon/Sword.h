// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMeleeWeapon.h"
#include "../../../../Interfaces/Weapon/MeleeWeapon.h"
#include "Sword.generated.h"




UCLASS()
class ROGUELIKE2DGAME_API USword : public UBaseMeleeWeapon
{
	GENERATED_BODY()
	
public:

	USword();

public:

	virtual bool DamageLevelUp() override;
	virtual bool SpeedAttackLevelUp() override;
};