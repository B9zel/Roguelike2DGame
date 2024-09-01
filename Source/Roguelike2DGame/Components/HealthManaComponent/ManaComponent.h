// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKE2DGAME_API UManaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UManaComponent();

public:

	UFUNCTION(BlueprintCallable)
	void SetMaxMana(int newMax);
	UFUNCTION(BlueprintPure)
	int GetMaxMana();

	UFUNCTION(BlueprintCallable)
	void SetMana(int newMana);
	UFUNCTION(BlueprintPure)
	int GetMana();

protected:

	UPROPERTY(EditAnywhere)
	int maxMana;
	UPROPERTY(EditAnywhere)
	int currentMana;
};
