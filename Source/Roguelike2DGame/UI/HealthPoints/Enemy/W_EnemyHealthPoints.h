// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EnemyHealthPoints.generated.h"



class UProgressBar;
class UHealthManaComponent;

UCLASS()
class ROGUELIKE2DGAME_API UW_EnemyHealthPoints : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	float BindPercentHealth();

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UProgressBar* PB_Health;

	UHealthManaComponent* healthBind;
public:

	const UProgressBar* GetHealthProgressBar();

	void SetHealthComponentBind(UHealthManaComponent* component);
};
