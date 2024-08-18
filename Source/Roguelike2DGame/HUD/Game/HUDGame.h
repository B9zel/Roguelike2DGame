// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../../Data/ResourceLoader.h"
#include <Runtime/UMG/Public/Blueprint/UserWidget.h>
#include "HUDGame.generated.h"




class UUserWidget;
class UW_GameMainMenu;
class UW_MenuSelectArtifacts;
class UHealthComponent;
class UW_MenuWeaponImprove;
class UResourceLoader;

struct LoaderHandle;


UENUM(BlueprintType)
enum class ETypeWidget : uint8
{
	MAIN_MENU = 0,
	SELECT_ARTIFACTS,
	WEAPON_IMPROVE_MENU
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
	UW_GameMainMenu* ShowGameMainMenu(const bool isShow, const int zOrder=0);
	UFUNCTION(BlueprintCallable)
	UW_MenuSelectArtifacts* ShowSelectArtifact(const bool isShow,const int zOrder = 0);

	UFUNCTION(BlueprintCallable)
	UW_MenuWeaponImprove* ShowWeaponImprove(const bool isShow,const int zOrder = 0);

protected:

	virtual void BeginPlay() override;

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
	/* @return true if can show a widget */
	bool ShowWidget(UUserWidget* widget, const int zOrder = 0);

	/* @return true if can remove a widget */
	bool RemoveWidget(UUserWidget* widget);
	
	void LoadWidgetClass(const ETypeWidget& widget);

	UClass* GetLoadedWidget(const ETypeWidget& widget);


public:

	UPROPERTY(BlueprintAssignable)
	FSwitchDispatch enableWdiget;
	UPROPERTY(BlueprintAssignable)
	FSwitchDispatch disableWdiget;

protected:

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_GameMainMenu> mainMenuClass;
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_MenuSelectArtifacts> menuSelecArtifactClass;
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_MenuWeaponImprove> menuWeaponImproveClass;


	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UW_GameMainMenu* mainMenuWidget;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UW_MenuSelectArtifacts* menuSelecArtifact;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UW_MenuWeaponImprove* menuWeaponImprove;

	TMap<ETypeWidget, LoaderHandle> cashWidget;

private:

	class UInstanceGame* m_Instance;
};


