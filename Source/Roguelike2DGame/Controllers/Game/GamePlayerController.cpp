// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "../../HUD/Game/HUDGame.h"



AGamePlayerController::AGamePlayerController()
{
	HUD = nullptr;
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	
}

void AGamePlayerController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);

	HUD = GetHUD<AHUDGame>();
	if (HUD != nullptr)
	{
		HUD->ShowGameMainMenu(true);
	}
}