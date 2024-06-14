// Fill out your copyright notice in the Description page of Project Settings.

#include "W_HeathPoints.h"
#include <Components/ProgressBar.h>
#include <Roguelike2DGame/Characters/MainCharacter/MainPaperCharacter.h>
#include "../../Components/HealthManaComponent/HealthManaComponent.h"


void UW_HeathPoints::NativeConstruct()
{
	Super::NativeConstruct();
	healthComponentOfCharacter = GetOwningPlayer()->GetPawn<AMainPaperCharacter>()->GetHealthComponent();

}

