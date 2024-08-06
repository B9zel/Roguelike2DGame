// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGame.h"
#include "../../UI/MainMenu/Game/W_GameMainMenu.h"
#include "../../UI/HealthPoints/Enemy/W_EnemyHealthPoints.h"
#include "../../UI/SelectArtifacts/W_MenuSelectArtifacts.h"
#include "../../UI/Services/W_MenuWeaponImprove.h"

#include "../../Components/HealthManaComponent/HealthComponent.h"



AHUDGame::AHUDGame()
{
	mainMenuWidget = nullptr;
	menuWeaponImprove = nullptr;
	menuSelecArtifactClass = nullptr;
}

UW_GameMainMenu* AHUDGame::ShowGameMainMenu(const bool isShow,const int zOrder)
{
	isShow ? enableWdiget.Broadcast(ETypeWidget::MAIN_MENU) : disableWdiget.Broadcast(ETypeWidget::MAIN_MENU);
	SwitchWidget<UW_GameMainMenu>(isShow, mainMenuWidget, mainMenuClass, zOrder);
	return mainMenuWidget.Get();
}

UW_MenuSelectArtifacts* AHUDGame::ShowSelectArtifact(const bool isShow, const int zOrder)
{
	isShow ? enableWdiget.Broadcast(ETypeWidget::SELECT_ARTIFACTS) : disableWdiget.Broadcast(ETypeWidget::SELECT_ARTIFACTS);
	SwitchWidget<UW_MenuSelectArtifacts, UClass>(isShow, menuSelecArtifact, menuSelecArtifactClass.LoadSynchronous(), zOrder);
	return menuSelecArtifact.Get();
}

UW_MenuWeaponImprove* AHUDGame::ShowWeaponImprove(const bool isShow, const int zOrder)
{
	isShow ? enableWdiget.Broadcast(ETypeWidget::WEAPON_IMPROVE_MENU) : disableWdiget.Broadcast(ETypeWidget::WEAPON_IMPROVE_MENU);
	SwitchWidget<UW_MenuWeaponImprove, UClass>(isShow, menuWeaponImprove, menuWeaponImproveClass.LoadSynchronous(), zOrder);

	return menuWeaponImprove.Get();
}

