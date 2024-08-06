// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelConfigDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API ULevelConfigDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/*
	*	Key int is level
	*	Value int is amount of souls for level up
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<int, int> levelSouls;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int maxLevel;
};
