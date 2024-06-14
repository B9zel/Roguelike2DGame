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

	//UFUNCTION(BlueprintCallable, BlueprintPure)
	//const class AMeleeEnemy* GetControlledCharacter();

	
	FVector GetDistancePatrolling();

protected:

	virtual void OnPossess(APawn* InPawn) override;

	
	UFUNCTION()
	void OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);

	//UFUNCTION()
	//virtual void OnRealoadAttackCharacter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnAttckCharacter();

	UFUNCTION()
	virtual void OnDeathControlledCharacter(AActor* actor);
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAIPerceptionComponent* perceptionAIComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isPatrollingMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeStay;

	UPROPERTY(EditAnywhere)
	FName isAttckKeyName;

	UPROPERTY(EditAnywhere)
	FName actorToAttackKey;

	UPROPERTY()
	AActor* actorToAttack;
	
	UPROPERTY(BlueprintReadOnly)
	AMeleeEnemy* controlledCharacter;

	UPROPERTY(EditAnywhere)
	FVector distancePatrolling;



};
