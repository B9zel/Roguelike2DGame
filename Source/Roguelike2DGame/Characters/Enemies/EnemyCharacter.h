// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BasePaperCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API AEnemyCharacter : public ABasePaperCharacter
{
	GENERATED_BODY()
public:

	AEnemyCharacter();

protected:

	UFUNCTION(BlueprintCallable)
	void SwitchDirectionX();
};
