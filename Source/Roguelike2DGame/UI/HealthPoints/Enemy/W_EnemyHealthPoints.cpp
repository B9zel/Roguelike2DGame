// Fill out your copyright notice in the Description page of Project Settings.


#include "W_EnemyHealthPoints.h"
#include <Components/ProgressBar.h>
#include <Kismet/KismetMathLibrary.h>
#include "../../../Components/HealthComponent/HealthComponent.h"




void UW_EnemyHealthPoints::NativeConstruct()
{
	Super::NativeConstruct();

	PB_Health->PercentDelegate.BindDynamic(this, &UW_EnemyHealthPoints::BindPercentHealth);
	PB_Health->SynchronizeProperties();
}

float UW_EnemyHealthPoints::BindPercentHealth()
{
	if (healthBind != nullptr)
	{
		return UKismetMathLibrary::NormalizeToRange(healthBind->GetCurrentHP(), 0, healthBind->GetMaxHP());
	}
	return 0.f;
}

const UProgressBar* UW_EnemyHealthPoints::GetHealthProgressBar()
{
	return PB_Health;
}

void UW_EnemyHealthPoints::SetHealthComponentBind(UHealthComponent* component)
{
	healthBind = component;
}
