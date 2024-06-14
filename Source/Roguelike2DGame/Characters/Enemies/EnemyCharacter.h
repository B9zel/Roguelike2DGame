// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BasePaperCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API AEnemyCharacter : public ABasePaperCharacter
{
	GENERATED_BODY()
public:

	AEnemyCharacter();
	
	//TArray<TEnumAsByte<EObjectTypeQuery>> GetBlockObjectPatrolling();

	virtual void OnDeath(AActor* deadActor) override;

	UFUNCTION(BlueprintCallable)
	void SwitchDirectionX();

protected:

	UPROPERTY(EditAnywhere, meta=(ClampMin="0"))
	uint32 countDropMoney;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABaseInteraction> moneyInteract;

};
