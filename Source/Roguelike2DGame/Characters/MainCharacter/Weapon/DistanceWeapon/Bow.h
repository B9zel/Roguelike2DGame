// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDistanceWeapon.h"

#include "Bow.generated.h"



class AArrow;
class AMainPaperCharacter;


UCLASS()
class ROGUELIKE2DGAME_API UBow : public UBaseDistanceWeapon
{
	GENERATED_BODY()

public:

	UBow();

public:

	virtual void StartAttack() override;
	virtual void StopAttack_Implementation() override;

	virtual bool DamageLevelUp() override;
	virtual bool SpeedAttackLevelUp() override;

protected:

	virtual void PostInitProperties() override;

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AArrow> projectileClass;

	UPROPERTY(EditAnywhere)
	int32 costOfUse;

protected:

	AMainPaperCharacter* owningPleryCharacter;
};
