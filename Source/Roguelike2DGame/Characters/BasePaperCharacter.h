// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BasePaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API ABasePaperCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

	ABasePaperCharacter();

protected:

	UFUNCTION(BlueprintCallable)
	virtual void OnAttack();
	UFUNCTION(BlueprintCallable)
	virtual void OnAttackHit();

	virtual void OnReloadAttack();

protected:

	UPROPERTY(EditAnywhere)
	class UHealthComponent* healthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeReloadAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool canAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float distanceAttack;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> targetEnums;

	FTimerHandle attackReloadTimer;
};
