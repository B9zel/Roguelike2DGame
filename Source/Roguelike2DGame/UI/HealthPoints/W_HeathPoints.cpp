// Fill out your copyright notice in the Description page of Project Settings.

#include "W_HeathPoints.h"
#include "../../Characters/MainCharacter/MainPaperCharacter.h"
#include "../../Components/HealthManaComponent/HealthComponent.h"
#include "../../GameModes/Game/MainGameMode.h"
#include "../../Data/Enums/ETypeScroll.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>




void UW_HeathPoints::NativeConstruct()
{
	Super::NativeConstruct();

	ownerCharacter = GetOwningPlayerPawn<AMainPaperCharacter>();
	ownerCharacter->improveStatDelegate.AddDynamic(this, &UW_HeathPoints::ImproveOwnerCharacter);
 	
	Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this))->spawnDeligate.AddDynamic(this, &UW_HeathPoints::PostInit);
}

void UW_HeathPoints::UpdateHealth(AActor* instigatorDamage)
{
	TB_CurrentHP->SetText(FText::FromString(FString::FromInt(healthComponentOfCharacter->GetCurrentHP())));
	PB_HealthPoints->SetPercent(static_cast<float>(healthComponentOfCharacter->GetCurrentHP()) / static_cast<float>(healthComponentOfCharacter->GetMaxHP()));
}

void UW_HeathPoints::ImproveOwnerCharacter(const ETypeScroll& typeImprove)
{
	if (typeImprove == ETypeScroll::HEALTH)
	{
		TB_MaxHP->SetText(FText::FromString(FString::FromInt(healthComponentOfCharacter->GetMaxHP())));
		PB_HealthPoints->SetPercent(static_cast<float>(healthComponentOfCharacter->GetCurrentHP()) / static_cast<float>(healthComponentOfCharacter->GetMaxHP()));
	}
}

void UW_HeathPoints::PostInit(AActor* actor)
{
	if (!healthComponentOfCharacter)
	{
		if (actor == ownerCharacter)
		{
			healthComponentOfCharacter = ownerCharacter->GetHealthComponent();
			check(healthComponentOfCharacter);
			healthComponentOfCharacter->takeDamageDelegate.AddDynamic(this, &UW_HeathPoints::UpdateHealth);

			TB_CurrentHP->SetText(FText::FromString(FString::FromInt(healthComponentOfCharacter->GetCurrentHP())));
			PB_HealthPoints->SetPercent(static_cast<float>(healthComponentOfCharacter->GetCurrentHP()) / healthComponentOfCharacter->GetMaxHP());
			TB_MaxHP->SetText(FText::FromString(FString::FromInt(healthComponentOfCharacter->GetMaxHP())));
		}
	}
}

