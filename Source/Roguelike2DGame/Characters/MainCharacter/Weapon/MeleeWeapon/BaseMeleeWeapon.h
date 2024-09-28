// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseWeapon.h"
#include "../../../../Interfaces/Weapon/IReloadableWeapon.h"
#include "../../../../Interfaces/Weapon/MeleeWeapon.h"

#include "BaseMeleeWeapon.generated.h"



UCLASS(Abstract, Blueprintable)
class ROGUELIKE2DGAME_API UBaseMeleeWeapon : public UBaseWeapon, public IMeleeWeapon, public IReloadableWeapon
{
	GENERATED_BODY()

public:

	virtual void Attack_Implementation() override;
	virtual void StartReload_Implementation() override;
	virtual void OnEndAnimationAttack() override;

	virtual void SetTimeReload(const float time) override;
	virtual	float GetTimeReload() override;

	UFUNCTION(BlueprintCallable)
	float GetDistanceAttack() { return distanceOfAttack; }

	void SetDistanceAttack(float distance);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	float distanceOfAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	float timeReload;
	UPROPERTY(EditAnywhere)
	float capsuleRadiusAttack;
	UPROPERTY(EditAnywhere)
	float capsuleHalfHeightAttack;

	// Value, that change recharge time
	UPROPERTY(EditAnywhere)
	float levelUpTimeReload;

};
