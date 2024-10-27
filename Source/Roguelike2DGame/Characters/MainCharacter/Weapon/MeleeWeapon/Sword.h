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

	virtual void PostInitProperties() override;

	virtual void StartAttack() override;
	virtual void Attack_Implementation();
	virtual void StartAnimAttack() override;
	virtual void OnEndAnimationAttack() override;
	virtual bool DamageLevelUp() override;
	virtual bool SpeedAttackLevelUp() override;

private:

	void ResetAttackAnim();

	UFUNCTION()
	void OnLendedOwnerCharacter(const FHitResult& Hit);

protected:

	UPROPERTY(EditAnywhere, Category = "Anim")
	FName SecondAttackAnimation;

	UPROPERTY(EditAnywhere)
	float TimeAttackCombo;

private:

	FTimerHandle m_TimeBetweenAttackHandle;
	bool m_CanUseSecondAttack;
};