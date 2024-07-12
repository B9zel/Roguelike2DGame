// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScrollDataAsset.generated.h"


enum class ETypeScroll : uint8;


UCLASS()
class ROGUELIKE2DGAME_API UScrollDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETypeScroll typeScroll;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1.0", UIMin = "0.0"))
	float multiplier;
};
