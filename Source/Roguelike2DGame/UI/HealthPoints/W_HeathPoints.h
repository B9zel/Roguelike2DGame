// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_HeathPoints.generated.h"


class UProgressBar;
class UHealthComponent;


UCLASS()
class ROGUELIKE2DGAME_API UW_HeathPoints : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_HealthPoints;

	class UHealthComponent* healthComponentOfCharacter;

protected:

	virtual void NativeConstruct() override;
	UFUNCTION()
	float BindPercentHealthPoints();

	
};
