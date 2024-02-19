// Fill out your copyright notice in the Description page of Project Settings.

#include "W_HeathPoints.h"
#include <Components/ProgressBar.h>
#include <Roguelike2DGame/Characters/MainCharacter/MainPaperCharacter.h>
#include "../../Components/HealthComponent/HealthComponent.h"


void UW_HeathPoints::NativeConstruct()
{
	Super::NativeConstruct();
	healthComponentOfCharacter = GetOwningPlayer()->GetPawn<AMainPaperCharacter>()->GetHealthComponent();

	PB_HealthPoints->PercentDelegate.BindDynamic(this, &UW_HeathPoints::BindPercentHealthPoints);
	PB_HealthPoints->SynchronizeProperties();
}

float UW_HeathPoints::BindPercentHealthPoints()
{
	if (healthComponentOfCharacter != nullptr)
	{
		if (healthComponentOfCharacter->GetMaxHP() != 0.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("%f"), healthComponentOfCharacter->GetCurrentHP() / healthComponentOfCharacter->GetMaxHP());
			return (float)healthComponentOfCharacter->GetCurrentHP() / (float)healthComponentOfCharacter->GetMaxHP();
		}
	}
	return 0.f;
}
