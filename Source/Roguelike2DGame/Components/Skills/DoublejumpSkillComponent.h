// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSkillComponent.h"
#include "DoublejumpSkillComponent.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API UDoublejumpSkillComponent : public UBaseSkillComponent
{
	GENERATED_BODY()

protected:

	virtual void Activate(bool bReset = false) override;
	
};
