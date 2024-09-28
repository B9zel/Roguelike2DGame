// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FinishStageWeapon.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UFinishStageWeapon : public UInterface
{
	GENERATED_BODY()
};

class ROGUELIKE2DGAME_API IFinishStageWeapon
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopAttack();
};