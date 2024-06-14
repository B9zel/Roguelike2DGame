// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_GameMainMenu.generated.h"


class UW_HeathPoints;
class UW_EnemyHealthPoints;

UCLASS()
class ROGUELIKE2DGAME_API UW_GameMainMenu : public UUserWidget
{
	GENERATED_BODY()
protected:

	
	//UPROPERTY(meta = (BindWidget))
	//UW_EnemyHealthPoints* bossHealthStat;

public:

	UW_HeathPoints* GetHeatlhStat();

	UW_EnemyHealthPoints* GetBossHeathStat();
};
