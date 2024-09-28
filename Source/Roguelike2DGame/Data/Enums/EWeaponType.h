#pragma once

#include "CoreMinimal.h"
#include "EWeaponType.generated.h"


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	SWORD = 0,
	BOW,
	SCYTHE
};