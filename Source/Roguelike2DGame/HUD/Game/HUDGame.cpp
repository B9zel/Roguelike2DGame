// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGame.h"
#include "../../UI/MainMenu/Game/W_GameMainMenu.h"
#include "../../UI/HealthPoints/Enemy/W_EnemyHealthPoints.h"
#include "../../Components/HealthManaComponent/HealthManaComponent.h"


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

bool AHUDGame::EnableEnemyHealthStat(UHealthManaComponent* bindComponent)
{
	if (mainMenuWidget != nullptr)
	{
		mainMenuWidget->GetBossHeathStat()->SetHealthComponentBind(bindComponent);
		mainMenuWidget->GetBossHeathStat()->SetVisibility(ESlateVisibility::Visible);
		
		return true;
	}
	return false;
}

bool AHUDGame::DisableEnemyHealthStat()
{
	if (mainMenuWidget != nullptr)
	{
		mainMenuWidget->GetBossHeathStat()->SetVisibility(ESlateVisibility::Collapsed);
		return true;
	}
	return false;
}
