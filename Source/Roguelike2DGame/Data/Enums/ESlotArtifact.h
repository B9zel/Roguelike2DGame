// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "ESlotArtifact.generated.h"



UENUM(BlueprintType)
enum class ESlotArtifact : uint8
{
	RIGHT_SLOT = 0,
	LEFT_SLOT
};
