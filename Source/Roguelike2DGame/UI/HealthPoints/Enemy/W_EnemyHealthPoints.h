// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EnemyHealthPoints.generated.h"



class UProgressBar;

UCLASS()
class ROGUELIKE2DGAME_API UW_EnemyHealthPoints : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_Health;
public:

	const UProgressBar* GetHealthProgressBar();
};
