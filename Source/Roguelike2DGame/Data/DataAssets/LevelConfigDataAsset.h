// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Structures/PairCost.h"
#include "LevelConfigDataAsset.generated.h"





UCLASS()
class ROGUELIKE2DGAME_API ULevelConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/*
	*	Key int is level
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<int, FPairCost> levelSouls;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int maxLevel;
};
