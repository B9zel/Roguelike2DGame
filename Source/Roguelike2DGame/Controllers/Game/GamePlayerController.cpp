// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "../../Components/Artifacts/BaseArtifactComponent.h"
#include "../../Characters/MainCharacter/MainPaperCharacter.h"
#include "../../Data/DataAssets/ArtifactUsedDataAsset.h"
#include "../../Data/Enums/ESlotArtifact.h"
#include "../../UI/Inventory/W_InventoryMenu.h"
#include "../../HUD/Game/HUDGame.h"
#include "../../InstanceGame.h"

#include <Blueprint/UserWidget.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <EnhancedInputSubsystems.h>





AGamePlayerController::AGamePlayerController()
{
	HUD				= nullptr;
	money			= 0;
	energyOfSouls	= 0;
}

void AGamePlayerController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);

	HUD = GetHUD<AHUDGame>();
	if (HUD)
	{
		HUD->ShowGameMainMenu(true);
	}
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (auto* inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (Input.controllerInputContext)
		{
			inputSystem->AddMappingContext(Input.controllerInputContext, 0);
		}
	}
	UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(InputComponent.Get());
	enhancedInput->BindAction(Input.inventoryCallAction, ETriggerEvent::Started, this, &AGamePlayerController::OnShowInventory);
}

void AGamePlayerController::OnShowInventory()
{
	if (HUD)
	{
		SetInputUIMode(HUD->ShowInventory(true));
	}
}

UBaseArtifactComponent* AGamePlayerController::BindArtifact(const ESlotArtifact slot, const TSoftClassPtr<UBaseArtifactComponent>& artifactBind)
{
	const bool isLeftArtifact = slot == ESlotArtifact::LEFT_SLOT;
	UBaseArtifactComponent** artifact = isLeftArtifact ? &activeArtifacts->leftArtifact.artifact : &activeArtifacts->rightArtifact.artifact;

	if ((*artifact))
	{
		(*artifact)->DestroyComponent(true);
	}
	if (artifactBind.IsValid())
	{
		*artifact = NewObject<UBaseArtifactComponent>(GetPawn(), artifactBind.Get());
		(*artifact)->RegisterComponent();
	}
	else
	{
		*artifact = nullptr;
	}
	return *artifact;
}


UArtifactUsedDataAsset* AGamePlayerController::GetArtifactDataAsset()
{
	if (!loaderArtifactAsset.IsValid())
	{
		ResourceLoader::ResourceSyncLoad(loaderArtifactAsset, activeArtifacts.ToSoftObjectPath());
	}

	return Cast<UArtifactUsedDataAsset>(ResourceLoader::GetData(loaderArtifactAsset));
}

void AGamePlayerController::SetInputUIMode(UUserWidget* focusWidget)
{
	if (!focusWidget) return;

	SetShowMouseCursor(true);

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(focusWidget->TakeWidget());
	SetInputMode(inputMode);
}

void AGamePlayerController::SetInputGameMode()
{
	SetShowMouseCursor(false);

	FInputModeGameOnly inputMode;
	SetInputMode(inputMode);
}

void AGamePlayerController::SetEnergyOfSouls(int32 number)
{
	if (number < 0)
	{
		UE_LOG(GameController, Warning, TEXT("Can't set negative number"));
		return;
	}
	energyOfSouls = number;
}

void AGamePlayerController::SetMoney(int32 newMoney)
{
	if (newMoney < 0)
	{
		UE_LOG(GameController, Warning, TEXT("Can't set negative value in money"));
		return;
	}
	money = newMoney;
}

void AGamePlayerController::AddMoney(int32 addMoney)
{
	if (addMoney < 0)
	{
		UE_LOG(GameController, Warning, TEXT("Can't add negative value in money"));
		return;
	}
	money += addMoney;
}

void AGamePlayerController::AddEnergyOfSouls(int32 addValue)
{
	if (addValue < 0)
	{
		UE_LOG(GameController, Warning, TEXT("Can't add negative value in energy of souls"));
		return;
	}
	energyOfSouls += addValue;
}

void AGamePlayerController::EnableCharacterMovement()
{
	GetCharacter()->GetCharacterMovement()->Activate();
}

void AGamePlayerController::DisableCharacterMovement()
{
	GetCharacter()->GetCharacterMovement()->Deactivate();
}

int32 AGamePlayerController::GetEnergyOfSouls()
{
	return energyOfSouls;
}