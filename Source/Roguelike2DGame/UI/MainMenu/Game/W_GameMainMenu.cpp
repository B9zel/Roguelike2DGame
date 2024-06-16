// Fill out your copyright notice in the Description page of Project Settings.


#include "W_GameMainMenu.h"
#include "../../HealthPoints/W_HeathPoints.h"
#include "../../HealthPoints/Enemy/W_EnemyHealthPoints.h"

UW_HeathPoints* UW_GameMainMenu::GetHeatlhStat()
{
	///return healthStat;
	return nullptr;
}

UW_EnemyHealthPoints* UW_GameMainMenu::GetBossHeathStat()
{
	return nullptr;//bossHealthStat;
}
