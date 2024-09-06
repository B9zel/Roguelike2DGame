// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../../Data/ResourceLoader.h"
#include <Runtime/UMG/Public/Blueprint/UserWidget.h>
#include "HUDGame.generated.h"




class UUserWidget;
class UW_GameMainMenu;
class UW_InventoryMenu;
class UW_MenuWeaponImprove;
class UW_SwapToEnergyOfSoulsMenu;
class UHealthComponent;
class ResourceLoader;
class AGamePlayerController;

struct LoaderHandle;


UENUM(BlueprintType)
enum class ETypeWidget : uint8
{
	MAIN_MENU = 0,
	INVENTORY_MENU,
	WEAPON_IMPROVE_MENU,
	SWAP_TO_ENERGY_OF_SOULS
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSwitchDispatch, const ETypeWidget&, widget);
DECLARE_LOG_CATEGORY_CLASS(HUD, Display, Display);



UCLASS()
class ROGUELIKE2DGAME_API AHUDGame : public AHUD
{
	GENERATED_BODY()

public:

	AHUDGame();

public:

	UFUNCTION(BlueprintCallable)
	UW_GameMainMenu*		ShowGameMainMenu(const bool isShow, const int zOrder=0);
	UFUNCTION(BlueprintCallable)
	UW_InventoryMenu*		ShowInventory(const bool isShow,const int zOrder = 0);
	UFUNCTION(BlueprintCallable)
	UW_MenuWeaponImprove*	ShowWeaponImprove(const bool isShow, const int zOrder = 0);
	UFUNCTION(BlueprintCallable)
	UW_SwapToEnergyOfSoulsMenu*	ShowSwapToEnergyOfSouls(const bool isShow, const int zOrder = 0);


	UClass* GetLoadedWidget(const ETypeWidget& widget);

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	template<class T>
	bool CreateUserWidget(T** inWidget, UClass* widgetClass, const bool isReset=false)
	{
		if (!(*inWidget) || isReset)
		{
			RemoveWidget(*inWidget);
			*inWidget = CreateWidget<T>(GetOwningPlayerController(), widgetClass);

			return true;
		}
		return false;
	}

	template<class T>
	bool SwitchWidget(const bool isShow, T** inWidget, UClass* widgetClass,const int zOrder)
	{
		if (!widgetClass)return false;

		CreateUserWidget<T>(inWidget, widgetClass);
		return isShow ? ShowWidget(*inWidget, zOrder) : RemoveWidget(*inWidget);
	}
	template<class T>
	void ShowTWidget(const bool isShow, const ETypeWidget& widget, T** widgetPtr, const int zOrder = 0)
	{
		if (isShow)
		{
			LoadWidgetClass(widget);
		}
		SwitchWidget<T>(isShow, widgetPtr, GetLoadedWidget(widget), zOrder);

		isShow ? enableWdiget.Broadcast(widget) : disableWdiget.Broadcast(widget);
	}

	/* @return true if can show a widget */
	bool ShowWidget(UUserWidget* widget, const int zOrder = 0);

	/* @return true if can remove a widget */
	bool RemoveWidget(UUserWidget* widget);

	
	void LoadWidgetClass(const ETypeWidget& widget);

	
public:

	UPROPERTY(BlueprintAssignable)
	FSwitchDispatch enableWdiget;
	UPROPERTY(BlueprintAssignable)
	FSwitchDispatch disableWdiget;

protected:


	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_GameMainMenu> mainMenuClass;
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_InventoryMenu> menuInventoryMenuClass;
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_MenuWeaponImprove> menuWeaponImproveClass;
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_SwapToEnergyOfSoulsMenu> menuSwapToEnergyOfSoulsClass;


	UPROPERTY(BlueprintReadOnly)
	UW_GameMainMenu* mainMenuWidget;
	UPROPERTY(BlueprintReadOnly)
	UW_InventoryMenu* menuInventory;
	UPROPERTY(BlueprintReadOnly)
	UW_MenuWeaponImprove* menuWeaponImprove;
	UPROPERTY(BlueprintReadOnly)
	UW_SwapToEnergyOfSoulsMenu* menuSwapToEnergyOfSouls;

	TMap<ETypeWidget, LoaderHandle> cashWidget;

private:

	AGamePlayerController* m_OwningController;
};


