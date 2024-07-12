// Fill out your copyright notice in the Description page of Project Settings.


#include "W_ManaPoints.h"
#include "../../Characters/MainCharacter/MainPaperCharacter.h"
#include "../../Components/HealthManaComponent/ManaComponent.h"
#include "../../GameModes/Game/MainGameMode.h"

#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>




void UW_ManaPoints::NativeConstruct()
{
	Super::NativeConstruct();

	Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this))->spawnDeligate.AddDynamic(this, &UW_ManaPoints::PostInit);
}

void UW_ManaPoints::PostInit(AActor* actorSpawn)
{
	if (!manaComponentOfCharacter)
	{
		if (actorSpawn == GetOwningPlayerPawn())
		{
			manaComponentOfCharacter = Cast<AMainPaperCharacter>(actorSpawn)->GetManaComponent();
			
			TB_CurrentMana->SetText(FText::FromString(FString::FromInt(manaComponentOfCharacter->GetMana())));
			PB_ManaPoints->SetPercent(static_cast<float>(manaComponentOfCharacter->GetMana()) / manaComponentOfCharacter->GetMaxMana());
			TB_MaxMana->SetText(FText::FromString(FString::FromInt(manaComponentOfCharacter->GetMaxMana())));
		}
	}
}
