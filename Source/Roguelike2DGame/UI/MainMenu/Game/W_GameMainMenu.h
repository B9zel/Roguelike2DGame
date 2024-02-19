// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_GameMainMenu.generated.h"


class UW_HeathPoints;


UCLASS()
class ROGUELIKE2DGAME_API UW_GameMainMenu : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget))
	UW_HeathPoints* healthStat;
};
