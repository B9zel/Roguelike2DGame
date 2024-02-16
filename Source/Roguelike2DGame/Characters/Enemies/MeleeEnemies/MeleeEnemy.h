// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyCharacter.h"
#include "MeleeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API AMeleeEnemy : public AEnemyCharacter
{
	GENERATED_BODY()
public:

	AMeleeEnemy();

protected:

	virtual void OnAttack() override;

	virtual void OnAttackHit() override;

	virtual void OnEndAttack() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* collisonBoxComponent;
};
