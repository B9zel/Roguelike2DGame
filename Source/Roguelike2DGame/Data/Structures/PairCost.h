// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PairCost.generated.h"



USTRUCT(BlueprintType)
struct FPairCost
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 souls;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 gold;
};