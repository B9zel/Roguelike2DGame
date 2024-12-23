// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseAIController.h"
#include "SlimeKingAIController.generated.h"



enum class EBossStage : uint8;

UCLASS()
class ROGUELIKE2DGAME_API ASlimeKingAIController : public ABaseAIController
{
	GENERATED_BODY()

protected:

	virtual void OnPossess(APawn* newPawn) override;

protected:

	UPROPERTY(EditAnywhere)
	FName NameOfEnumStage;

private:

	UFUNCTION()
	void OnSwitchStage(const EBossStage& newStage);

};
