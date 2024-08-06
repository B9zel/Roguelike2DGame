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
	
	virtual void OnDeath(AActor* deadActor, AActor* Instigator) override;

	UFUNCTION(BlueprintCallable)
	void SwitchDirectionX();



	UFUNCTION(BlueprintCallable)
	int GetSoulsDrop() { return countDropSouls; }
	UFUNCTION(BlueprintCallable)
	float GetDistanceAttack() { return distanceAttack; }
	UFUNCTION(BlueprintCallable)
	int GetDamage() { return damage; }
	UFUNCTION(BlueprintCallable)
	TArray<TEnumAsByte<EObjectTypeQuery>>& GetTypesAttackCollision() { return typesAttackCollision; }

	void SetDamage(int newDamage);
	void SetDistanceAttack(float distance);

protected:

	// Moneys
	UPROPERTY(EditAnywhere, meta=(ClampMin="0", UIMin = "0"))
	uint32 countDropMoney;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseInteraction> moneyInteract;

	// Soul
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = "0"))
	int countDropSouls;


	// Attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	int damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float distanceAttack;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> typesAttackCollision;

	UPROPERTY(EditAnywhere)
	float capsuleRadiusAttack;
	UPROPERTY(EditAnywhere)
	float capsuleHalfHeightAttack;
};
