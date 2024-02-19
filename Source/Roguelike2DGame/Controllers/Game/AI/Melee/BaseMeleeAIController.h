// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseMeleeAIController.generated.h"

class AMeleeEnemy;


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

	void SetIsImmediatelyAttack(bool Immediately);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAttackMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isPatrollingMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float distanceVisionOfPatrolling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeStay;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* toAttackCharacter;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AMeleeEnemy* controlledCharacter;


	UPROPERTY(EditAnywhere)
	bool isImmediatelyAttack;

protected:

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	virtual void OnRealoadAttackCharacter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnAttckCharacter();
};
