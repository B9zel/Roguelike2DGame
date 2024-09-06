// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Structures/PairCost.h"
#include "CostOfWeaponsDataAsset.generated.h"



enum class EWeaponType : uint8;


UCLASS()
class ROGUELIKE2DGAME_API UCostOfWeaponsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EWeaponType, FPairCost> costWeapons;
};
