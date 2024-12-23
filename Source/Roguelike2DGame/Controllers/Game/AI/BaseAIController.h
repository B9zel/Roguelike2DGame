// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ROGUELIKE2DGAME_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual void JumpSetup();

	UFUNCTION(BlueprintCallable)
	virtual void StopJumpSetup();

protected:

	UPROPERTY(EditAnywhere, Category = "Init param")
	float gravityJump;

	float defaultGravityScale;
};
