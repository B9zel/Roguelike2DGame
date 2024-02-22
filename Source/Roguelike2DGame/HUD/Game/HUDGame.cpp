// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGame.h"
#include "../../UI/MainMenu/Game/W_GameMainMenu.h"
#include "../../UI/HealthPoints/Enemy/W_EnemyHealthPoints.h"


AHUDGame::AHUDGame()
{
	mainMenuWidget = nullptr;

}

bool AHUDGame::ShowGameMainMenu(bool isShow,int zOrder)
{
	if (isShow)
	{
		if (mainMenuWidget == nullptr)
			mainMenuWidget = CreateWidget<UW_GameMainMenu>(GetOwningPlayerController(), mainMenuClass);
		mainMenuWidget->AddToViewport(zOrder);

		return true;
	}
	else if (mainMenuWidget != nullptr)
	{
		mainMenuWidget->RemoveFromParent();

		return true;
	}
	return false;
}

bool AHUDGame::ShowEnemyHealthStat(bool isShow)
{
	if (mainMenuWidget != nullptr)
	{
		if (isShow)
		{
			mainMenuWidget->GetBossHeathStat()->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			mainMenuWidget->GetBossHeathStat()->SetVisibility(ESlateVisibility::Collapsed);
		}
		return true;
	}
	return false;
}
