// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMeleeWeapon.h"
#include "Scythe.generated.h"




UCLASS()
class ROGUELIKE2DGAME_API UScythe : public UBaseMeleeWeapon
{
	GENERATED_BODY()

public:

	UScythe();

public:

	virtual void PostInitProperties() override;
	virtual bool DamageLevelUp() override;
	virtual bool SpeedAttackLevelUp() override;
	virtual void StartAttack() override;
	virtual void OnEndAnimationAttack() override;
	
private:

	UFUNCTION()
	void OnLendedOwnerCharacter(const FHitResult& Hit);
};
