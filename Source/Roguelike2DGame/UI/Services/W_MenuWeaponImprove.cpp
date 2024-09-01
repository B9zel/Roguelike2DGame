// Fill out your copyright notice in the Description page of Project Settings.


#include "W_MenuWeaponImprove.h"
#include "../../Controllers/Game/GamePlayerController.h"
#include "../../HUD/Game/HUDGame.h"



FReply UW_MenuWeaponImprove::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply res = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (keyExit != InKeyEvent.GetKey()) return res;

	if (auto* owningController = GetOwningPlayer<AGamePlayerController>())
	{
		owningController->GetHUD<AHUDGame>()->ShowWeaponImprove(false);
		owningController->SetInputGameMode();
		owningController->EnableCharacterMovement();
	}	
    return res;
}
