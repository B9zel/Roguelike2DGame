// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDGame.generated.h"


UENUM(BlueprintType)
enum class ETypeWidget : uint8
{
	MAIN_MENU = 0,
	SELECT_ARTIFACTS,
	WEAPON_IMPROVE_MENU
};

class UUserWidget;
class UW_GameMainMenu;
class UW_MenuSelectArtifacts;
class UHealthComponent;
class UW_MenuWeaponImprove;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSwitchDispatch, const ETypeWidget&, widget);




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

private:

	template<class T,class U>
	bool CreateUserWidget(TObjectPtr<T>& inWidget, const TSubclassOf<U>& widgetClass, const bool isReset=false)
	{
		if (!inWidget || isReset)
		{
			RemoveWidget(inWidget);
			inWidget = CreateWidget<T>(GetOwningPlayerController(), widgetClass.Get());
			return true;
		}
		return false;
	}

	/* @return true if can show a widget */
	template<class T>
	bool ShowWidget(const TObjectPtr<T>& widget,const int zOrder=0)
	{
		if (widget)
		{
			widget->AddToViewport(zOrder);
			return true;
		}
		return false;
	}
	/* @return true if can remove a widget */
	template<class T>
	bool RemoveWidget(const TObjectPtr<T>& widget)
	{
		if (widget)
		{
			widget->RemoveFromParent();
			return true;
		}
		return false;
	}
	template<class T, class U=T>
	bool SwitchWidget(const bool isShow, TObjectPtr<T>& inWidget,const TSubclassOf<U>& widgetClass,const int zOrder)
	{
		CreateUserWidget(inWidget, widgetClass);
		return isShow ? ShowWidget(inWidget, zOrder) : RemoveWidget(inWidget);
	}

public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_GameMainMenu> mainMenuClass;
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_MenuSelectArtifacts> menuSelecArtifactClass;
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_MenuWeaponImprove> menuWeaponImproveClass;

	UPROPERTY(BlueprintAssignable)
	FSwitchDispatch enableWdiget;
	UPROPERTY(BlueprintAssignable)
	FSwitchDispatch disableWdiget;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UW_GameMainMenu> mainMenuWidget;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UW_MenuSelectArtifacts> menuSelecArtifact;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UW_MenuWeaponImprove> menuWeaponImprove;
};


