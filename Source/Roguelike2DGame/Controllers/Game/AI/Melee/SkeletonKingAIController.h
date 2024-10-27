// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SkeletonKingAIController.generated.h"



class ASkeletonKing;


UCLASS()
class ROGUELIKE2DGAME_API ASkeletonKingAIController : public AAIController
{
	GENERATED_BODY()

public:

	ASkeletonKingAIController();

public:

	UFUNCTION(BlueprintCallable)
	void JumpSetup();

	UFUNCTION(BlueprintCallable)
	void StopJumpSetup();

protected:

	virtual void OnPossess(APawn* PawnTo) override;

protected:

	UPROPERTY(BlueprintReadOnly)
	ASkeletonKing* owningCharacter;

	UPROPERTY(EditAnywhere, Category="Init param")
	float gravityJump;

private:

	float defaultGravityScale;
};
