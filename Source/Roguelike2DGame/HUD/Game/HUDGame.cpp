// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGame.h"
#include "../../UI/SelectArtifacts/W_MenuSelectArtifacts.h"
#include "../../UI/HealthPoints/Enemy/W_EnemyHealthPoints.h"
#include "../../UI/MainMenu/Game/W_GameMainMenu.h"
#include "../../UI/Services/W_MenuWeaponImprove.h"

#include "../../Components/HealthManaComponent/HealthComponent.h"


#include "../../InstanceGame.h"

#include <Kismet/GameplayStatics.h>



AHUDGame::AHUDGame()
{
	mainMenuWidget = nullptr;
	menuWeaponImprove = nullptr;
	menuSelecArtifactClass = nullptr;
}

void AHUDGame::BeginPlay()
{
	Super::BeginPlay();

	m_Instance = Cast<UInstanceGame>(UGameplayStatics::GetGameInstance(this));
}


UW_GameMainMenu* AHUDGame::ShowGameMainMenu(const bool isShow,const int zOrder)
{
	if (isShow)
	{
		LoadWidgetClass(ETypeWidget::MAIN_MENU);
	}
	SwitchWidget<UW_GameMainMenu>(isShow, &mainMenuWidget, GetLoadedWidget(ETypeWidget::MAIN_MENU), zOrder);

	isShow ? enableWdiget.Broadcast(ETypeWidget::MAIN_MENU) : disableWdiget.Broadcast(ETypeWidget::MAIN_MENU);
	return mainMenuWidget;
}

UW_MenuSelectArtifacts* AHUDGame::ShowSelectArtifact(const bool isShow, const int zOrder)
{
	if (isShow)
	{
		LoadWidgetClass(ETypeWidget::SELECT_ARTIFACTS);
	}
	SwitchWidget<UW_MenuSelectArtifacts>(isShow, &menuSelecArtifact, GetLoadedWidget(ETypeWidget::SELECT_ARTIFACTS), zOrder);

	isShow ? enableWdiget.Broadcast(ETypeWidget::SELECT_ARTIFACTS) : disableWdiget.Broadcast(ETypeWidget::SELECT_ARTIFACTS);
	return menuSelecArtifact;
}

UW_MenuWeaponImprove* AHUDGame::ShowWeaponImprove(const bool isShow, const int zOrder)
{
	if (isShow)
	{
		LoadWidgetClass(ETypeWidget::WEAPON_IMPROVE_MENU);
	}
	SwitchWidget<UW_MenuWeaponImprove>(isShow, &menuWeaponImprove, GetLoadedWidget(ETypeWidget::SELECT_ARTIFACTS), zOrder);

	isShow ? enableWdiget.Broadcast(ETypeWidget::WEAPON_IMPROVE_MENU) : disableWdiget.Broadcast(ETypeWidget::WEAPON_IMPROVE_MENU);
	return menuWeaponImprove;
}



bool AHUDGame::ShowWidget(UUserWidget* widget, const int zOrder)
{
	if (widget)
	{
		widget->AddToViewport(zOrder);
		return true;
	}
	return false;
}

bool AHUDGame::RemoveWidget(UUserWidget* widget)
{
	if (widget)
	{
		widget->RemoveFromParent();
		return true;
	}
	return false;
}

void AHUDGame::LoadWidgetClass(const ETypeWidget& widget)
{
	if (cashWidget.Contains(widget)) return;

	LoaderHandle loadHandl;

	switch (widget)
	{
	case ETypeWidget::MAIN_MENU:
	{
		if (mainMenuClass.IsValid())
		{
			UResourceLoader::ResourceSyncLoad(loadHandl, mainMenuClass.ToSoftObjectPath());
			break;
		}
		UE_LOG(HUD, Display, TEXT("Can't laod \"main menu class\""));
		return;
	}
	case ETypeWidget::SELECT_ARTIFACTS:
	{
		if (menuSelecArtifactClass.IsValid())
		{
			UResourceLoader::ResourceSyncLoad(loadHandl, menuSelecArtifactClass.ToSoftObjectPath());
			break;
		}
		UE_LOG(HUD, Display, TEXT("Can't load \"select artifact class\" "));
		return;
	}
	case ETypeWidget::WEAPON_IMPROVE_MENU:
	{
		if (menuWeaponImproveClass.IsValid())
		{
			UResourceLoader::ResourceSyncLoad(loadHandl, menuWeaponImproveClass.ToSoftObjectPath());
			break;
		}
		UE_LOG(HUD, Display, TEXT("Can't load \"weapon improve class\" "));
		return;
	}
	default:
		throw std::exception("The \"cashWodget\" does't save input type widget");
	}

	cashWidget.Add(widget, loadHandl);
}

UClass* AHUDGame::GetLoadedWidget(const ETypeWidget& widget)
{
	if (cashWidget.Contains(widget))
	{
		return Cast<UClass>(UResourceLoader::GetData(*cashWidget.Find(widget)));
	}
	return nullptr;
}
