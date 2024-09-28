// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseWeapon.h"
#include "../../../../Interfaces/Weapon/FinishStageWeapon.h"
#include "BaseDistanceWeapon.generated.h"





UCLASS(Abstract, Blueprintable)
class ROGUELIKE2DGAME_API UBaseDistanceWeapon : public UBaseWeapon, public IFinishStageWeapon
{
	GENERATED_BODY()
	
public:

	UBaseDistanceWeapon();

public:

	virtual void SetTimeReload(const float rate) override;
	virtual float GetTimeReload() override;

protected:
	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampUI = "0.0"))
	float rateReload;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampUI = "0.0"))
	float levelUpRateReload;
};
