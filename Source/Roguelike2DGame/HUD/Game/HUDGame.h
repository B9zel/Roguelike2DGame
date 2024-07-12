// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDGame.generated.h"


UENUM(BlueprintType)
enum class ETypeWidget : uint8
{
	MAIN_MENU = 0,
	SELECT_ARTIFACTS
};

class UUserWidget;
class UW_GameMainMenu;
class UW_MenuSelectArtifacts;
class UHealthComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSwitchDispatch, const ETypeWidget&, widget);




UCLASS()
class ROGUELIKE2DGAME_API AHUDGame : public AHUD
{
	GENERATED_BODY()

public:

	AHUDGame();

	UFUNCTION(BlueprintCallable)
	bool ShowGameMainMenu(bool isShow, int zOrder=0);
	UFUNCTION(BlueprintCallable)
	bool ShowSelectArtifact(bool isShow, int zOrder = 0);

private:

	template<class T>
	bool ShowWidget(bool isShow, TObjectPtr<T>& inWidget, TSubclassOf<UUserWidget> widgetClass, int zOrder)
	{
		if (isShow)
		{
			if (!inWidget)
				inWidget = CreateWidget<T>(GetOwningPlayerController(), widgetClass);
			inWidget->AddToViewport(zOrder);

			return true;
		}
		else if (inWidget)
		{
			inWidget->RemoveFromParent();

			return true;
		}
		return false;
	}

public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_GameMainMenu> mainMenuClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_MenuSelectArtifacts> menuSelecArtifactClass;

	UPROPERTY(BlueprintAssignable)
	FSwitchDispatch enableWdiget;
	UPROPERTY(BlueprintAssignable)
	FSwitchDispatch disableWdiget;

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UW_GameMainMenu> mainMenuWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UW_MenuSelectArtifacts> menuSelecArtifact;
};


