// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "../../HUD/Game/HUDGame.h"
#include "../../Components/Artifacts/BaseArtifactComponent.h"
#include "../../InstanceGame.h"

#include <Kismet/GameplayStatics.h>





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

int32 AGamePlayerController::GetMoney()
{
	return money;
}

void AGamePlayerController::SetMoney(int32 newMoney)
{
	if (newMoney < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't set negative value in money"));
		return;
	}
	money = newMoney;
}

void AGamePlayerController::AddMoney(int32 addMoney)
{
	if (addMoney < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't add negative value in money"));
		return;
	}
	money += addMoney;
}
