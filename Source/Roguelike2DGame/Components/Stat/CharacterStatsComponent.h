// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKE2DGAME_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UCharacterStatsComponent();

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAttacking() { return isAttacking; }

	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool attack);

	UFUNCTION(BlueprintCallable)
	float GetTimeReloadAttack() { return timeReloadAttack; }

	UFUNCTION(BlueprintCallable)
	bool IsCanAttack() { return canAttack; }


	UFUNCTION(BlueprintCallable)
	bool GetCanAttack() { return canAttack; }

	
	void SetTimeReloadAttack(float time);
	void SetCanAttack(bool isAttack) { canAttack = isAttack; }
	
protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeReloadAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool canAttack;

	bool isAttacking;	
};
