// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseMeleeAIController.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API ABaseMeleeAIController : public AAIController
{
	GENERATED_BODY()
public:

	ABaseMeleeAIController();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const class AMeleeEnemy* GetControlledCharacter();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const class ACharacter* GetToAttackCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAttackMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isPatrollingMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float distanceVisionOfPatrolling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeStay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ACharacter* toAttackCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMeleeEnemy* controlledCharacter;

protected:

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	virtual void OnRealoadAttackCharacter();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnAttckCharacter();
};
