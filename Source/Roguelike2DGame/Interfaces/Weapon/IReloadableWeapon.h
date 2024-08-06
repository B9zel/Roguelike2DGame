// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IReloadableWeapon.generated.h"


UINTERFACE(MinimalAPI)
class UReloadableWeapon : public UInterface
{
	GENERATED_BODY()
};


class ROGUELIKE2DGAME_API IReloadableWeapon
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void StartReload();
};
