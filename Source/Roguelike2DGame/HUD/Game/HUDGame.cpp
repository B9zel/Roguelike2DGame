// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGame.h"
#include "../../UI/MainMenu/Game/W_GameMainMenu.h"

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
	}
	else if (mainMenuWidget != nullptr)
	{
		mainMenuWidget->RemoveFromParent();
	}
	return false;
}
