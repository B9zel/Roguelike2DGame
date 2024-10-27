// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BasePaperCharacter.h"
#include "EnemyCharacter.generated.h"




UCLASS(Abstract)
class ROGUELIKE2DGAME_API AEnemyCharacter : public ABasePaperCharacter
{
	GENERATED_BODY()
public:

	AEnemyCharacter();

public:

	virtual void OnDeath_Implementation(AActor* deadActor, AActor* Instigator) override;

	UFUNCTION(BlueprintCallable)
	void SwitchDirectionX();


	UFUNCTION(BlueprintCallable)
	int GetSoulsDrop() { return countDropSouls; }
	UFUNCTION(BlueprintCallable)
	float GetDistanceAttack() { return distanceAttack; }
	UFUNCTION(BlueprintPure)
	int GetDamage() { return damage; }
	UFUNCTION(BlueprintCallable)
	TArray<TEnumAsByte<EObjectTypeQuery>>& GetTypesAttackCollision() { return typesAttackCollision; }

	void SetDamage(int newDamage);
	void SetDistanceAttack(float distance);

	void Destroyer();

protected:

	virtual void Tick(float deltaTime) override;

protected:

	UPROPERTY(EditAnywhere)
	float timeDestroyAfterDeath;

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	float distanceAttack;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = "0"))
	float capsuleRadiusAttack;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = "0"))
	float capsuleHalfHeightAttack;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> typesAttackCollision;
};
