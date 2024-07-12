// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BasePaperCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ROGUELIKE2DGAME_API AEnemyCharacter : public ABasePaperCharacter
{
	GENERATED_BODY()
public:

	AEnemyCharacter();
	

	UFUNCTION(BlueprintCallable)
	float GetDistanceAttack() { return distanceAttack; }

	UFUNCTION(BlueprintCallable)
	int GetDamage() { return damage; }


	void SetDamage(int newDamage);
	void SetDistanceAttack(float distance);

	virtual void OnDeath(AActor* deadActor) override;

	UFUNCTION(BlueprintCallable)
	void SwitchDirectionX();

protected:

	UPROPERTY(EditAnywhere, meta=(ClampMin="0"))
	uint32 countDropMoney;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseInteraction> moneyInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	int damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float distanceAttack;

	UPROPERTY(EditAnywhere)
	float capsuleRadiusAttack;

	UPROPERTY(EditAnywhere)
	float capsuleHalfHeightAttack;
};
