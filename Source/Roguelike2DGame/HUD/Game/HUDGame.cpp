// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGame.h"
#include "../../UI/Inventory/W_InventoryMenu.h"
#include "../../UI/HealthPoints/Enemy/W_EnemyHealthPoints.h"
#include "../../UI/MainMenu/Game/W_GameMainMenu.h"
#include "../../UI/Services/W_MenuWeaponImprove.h"
#include "../../UI/Services/Exchanger/W_SwapToEnergyOfSoulsMenu.h"

#include "../../Components/HealthManaComponent/HealthComponent.h"
#include "../../Controllers/Game/GamePlayerController.h"
#include "../../Data/DataAssets/ArtifactUsedDataAsset.h"
#include "../../Data/Enums/ESlotArtifact.h"




AHUDGame::AHUDGame()
{
	mainMenuWidget			= nullptr;
	menuWeaponImprove		= nullptr;
	menuInventory			= nullptr;
	menuSwapToEnergyOfSouls = nullptr;
}

void AHUDGame::BeginPlay()
{
	Super::BeginPlay();
	m_OwningController = Cast<AGamePlayerController>(GetOwningPlayerController());
	if (!m_OwningController)
	{
		UE_LOG(HUD, Warning, TEXT("Can't get the controller"));
	}
}

void AHUDGame::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	mainMenuWidget			= nullptr;
	menuWeaponImprove		= nullptr;
	menuInventory			= nullptr;
	menuSwapToEnergyOfSouls = nullptr;
}


UW_GameMainMenu* AHUDGame::ShowGameMainMenu(const bool isShow,const int zOrder)
{
	ShowTWidget<UW_GameMainMenu>(isShow, ETypeWidget::MAIN_MENU, &mainMenuWidget, zOrder);
	return mainMenuWidget;
}

UW_InventoryMenu* AHUDGame::ShowInventory(const bool isShow, const int zOrder)
{
	ShowTWidget<UW_InventoryMenu>(isShow, ETypeWidget::INVENTORY_MENU, &menuInventory, zOrder);
	return menuInventory;
}

UW_MenuWeaponImprove* AHUDGame::ShowWeaponImprove(const bool isShow, const int zOrder)
{
	ShowTWidget<UW_MenuWeaponImprove>(isShow, ETypeWidget::WEAPON_IMPROVE_MENU, &menuWeaponImprove, zOrder);
	return menuWeaponImprove;
}

UW_SwapToEnergyOfSoulsMenu* AHUDGame::ShowSwapToEnergyOfSouls(const bool isShow, const int zOrder)
{
	ShowTWidget<UW_SwapToEnergyOfSoulsMenu>(isShow, ETypeWidget::SWAP_TO_ENERGY_OF_SOULS, &menuSwapToEnergyOfSouls, zOrder);
	return menuSwapToEnergyOfSouls;
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
		if (!(ResourceLoader::ResourceSyncLoad(loadHandl, mainMenuClass.ToSoftObjectPath()).IsValid()))
		{ 
			UE_LOG(HUD, Display, TEXT("Can't laod \"main menu class\""));
			return;
		}
		
		break;
	}
	case ETypeWidget::INVENTORY_MENU:
	{
		if (!(ResourceLoader::ResourceSyncLoad(loadHandl, menuInventoryMenuClass.ToSoftObjectPath()).IsValid()))
		{
			UE_LOG(HUD, Display, TEXT("Can't load \"inventory menu class\" "));
			return;
		}
		
		break;
	}
	case ETypeWidget::WEAPON_IMPROVE_MENU:
	{
		if (!(ResourceLoader::ResourceSyncLoad(loadHandl, menuWeaponImproveClass.ToSoftObjectPath()).IsValid()))
		{
			UE_LOG(HUD, Display, TEXT("Can't load \"weapon improve class\" "));
			return;
		}
		break;
	}
	case ETypeWidget::SWAP_TO_ENERGY_OF_SOULS:
	{
		if (!(ResourceLoader::ResourceSyncLoad(loadHandl, menuSwapToEnergyOfSoulsClass.ToSoftObjectPath()).IsValid()))
		{
			UE_LOG(HUD, Display, TEXT("Can't load \"weapon improve class\" "));
			return;
		}
		break;
	}
	default:
		UE_LOG(HUD, Warning, TEXT("The \"cashWidget\" does't save input type widget"));
		return;
	}

	cashWidget.Add(widget, loadHandl);
}

UClass* AHUDGame::GetLoadedWidget(const ETypeWidget& widget)
{
	if (cashWidget.Contains(widget))
	{
		return Cast<UClass>(ResourceLoader::GetData(*cashWidget.Find(widget)));
	}
	return nullptr;
}
