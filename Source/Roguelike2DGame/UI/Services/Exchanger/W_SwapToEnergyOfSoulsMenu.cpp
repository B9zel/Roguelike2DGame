// Fill out your copyright notice in the Description page of Project Settings.


#include "W_SwapToEnergyOfSoulsMenu.h"
#include "../../../Controllers/Game/GamePlayerController.h"
#include "../../../HUD/Game/HUDGame.h"


FReply UW_SwapToEnergyOfSoulsMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    FReply res = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (escapeKey == InKeyEvent.GetKey())
	{
		auto* owningController = GetOwningPlayer<AGamePlayerController>();
		owningController->GetHUD<AHUDGame>()->ShowSwapToEnergyOfSouls(false);
		owningController->SetInputGameMode();
	}

    return res;
}
