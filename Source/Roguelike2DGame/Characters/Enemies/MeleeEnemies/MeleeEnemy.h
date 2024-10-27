// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyCharacter.h"
#include "MeleeEnemy.generated.h"




UCLASS(Abstract)
class ROGUELIKE2DGAME_API AMeleeEnemy : public AEnemyCharacter
{
	GENERATED_BODY()
public:

	AMeleeEnemy();

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetTimeStayPatrolling();


	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAttacking() { return isAttacking; }
	UFUNCTION(BlueprintCallable)
	float GetTimeReloadAttack() { return timeReloadAttack; }
	UFUNCTION(BlueprintCallable)
	bool GetCanAttack() { return canAttack; }


	UFUNCTION(BlueprintCallable)
	void SetTimeReloadAttack(float time);
	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool attack) { isAttacking = attack; }
	UFUNCTION(BlueprintCallable)
	void SetCanAttack(bool isAttack) { canAttack = isAttack; }


	virtual void OnAttack() override;
	virtual void OnEndAnimAttack() override;
	virtual void OnAttackHit() override;

protected:

	virtual void OnReloadAttack() override;

protected:

	UPROPERTY(EditAnywhere, meta=(ClampMin="0", UIMin="0"))
	float timeStayInPatrolling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	float timeReloadAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool canAttack;

	bool isAttacking;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* collisonBoxComponent;
};
