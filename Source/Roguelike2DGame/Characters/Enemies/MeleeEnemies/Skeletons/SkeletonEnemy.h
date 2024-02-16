// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MeleeEnemy.h"
#include "SkeletonEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API ASkeletonEnemy : public AMeleeEnemy
{
	GENERATED_BODY()

protected:

	virtual void OnAttack() override;

	virtual void OnReloadAttack() override;

	virtual void OnDeath(AActor* deadActor) override;

	virtual void OnTakeDamage(AActor* instigatorDamage) override;
};
