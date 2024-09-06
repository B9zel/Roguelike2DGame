// Fill out your copyright notice in the Description page of Project Settings.


#include "W_InventoryMenu.h"
#include "../../Controllers/Game/GamePlayerController.h"
#include "../../HUD/Game/HUDGame.h"


FReply UW_InventoryMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply res = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (escapeKey == InKeyEvent.GetKey())
	{
		AGamePlayerController* controller = GetOwningPlayer<AGamePlayerController>();
		controller->GetHUD<AHUDGame>()->ShowInventory(false);
		controller->SetInputGameMode();
	}

	return res;
}
