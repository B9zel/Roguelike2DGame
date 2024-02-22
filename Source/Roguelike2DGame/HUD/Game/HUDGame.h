// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDGame.generated.h"

class UW_GameMainMenu;



UCLASS()
class ROGUELIKE2DGAME_API AHUDGame : public AHUD
{
	GENERATED_BODY()

public:

	AHUDGame();

	bool ShowGameMainMenu(bool isShow, int zOrder=0);

	bool ShowEnemyHealthStat(bool isShow);

public:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_GameMainMenu> mainMenuClass;

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UW_GameMainMenu* mainMenuWidget;
};
