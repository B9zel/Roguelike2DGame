// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGame.h"
#include "../../UI/MainMenu/Game/W_GameMainMenu.h"
#include "../../UI/HealthPoints/Enemy/W_EnemyHealthPoints.h"
#include "../../Components/HealthManaComponent/HealthComponent.h"
#include "../../UI/SelectArtifacts/W_MenuSelectArtifacts.h"



AHUDGame::AHUDGame()
{
	mainMenuWidget = nullptr;

}

bool AHUDGame::ShowGameMainMenu(bool isShow,int zOrder)
{
	isShow ? enableWdiget.Broadcast(ETypeWidget::MAIN_MENU) : disableWdiget.Broadcast(ETypeWidget::MAIN_MENU);
	return ShowWidget<UW_GameMainMenu>(isShow, mainMenuWidget, mainMenuClass, zOrder);
}

bool AHUDGame::ShowSelectArtifact(bool isShow, int zOrder)
{
	isShow ? enableWdiget.Broadcast(ETypeWidget::SELECT_ARTIFACTS) : disableWdiget.Broadcast(ETypeWidget::SELECT_ARTIFACTS);
	return ShowWidget<UW_MenuSelectArtifacts>(isShow, menuSelecArtifact, menuSelecArtifactClass, zOrder);
}

