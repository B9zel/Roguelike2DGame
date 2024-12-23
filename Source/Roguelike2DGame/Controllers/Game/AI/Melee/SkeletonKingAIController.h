// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseAIController.h"
#include "SkeletonKingAIController.generated.h"



class ASkeletonKing;


UCLASS()
class ROGUELIKE2DGAME_API ASkeletonKingAIController : public ABaseAIController
{
	GENERATED_BODY()

public:

	ASkeletonKingAIController();

protected:

	virtual void OnPossess(APawn* PawnTo) override;

protected:

	UPROPERTY(BlueprintReadOnly)
	ASkeletonKing* owningCharacter;
};
