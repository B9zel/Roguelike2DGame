// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DistanceWeapon.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UDistanceWeapon : public UInterface
{
	GENERATED_BODY()
};

class ROGUELIKE2DGAME_API IDistanceWeapon
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartAttack();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopAttack();
};