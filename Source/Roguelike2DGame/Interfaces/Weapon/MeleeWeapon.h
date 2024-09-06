// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeleeWeapon.generated.h"



UINTERFACE(MinimalAPI, Blueprintable)
class  UMeleeWeapon : public UInterface
{
	GENERATED_BODY()
};


class ROGUELIKE2DGAME_API IMeleeWeapon
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Attack();
};