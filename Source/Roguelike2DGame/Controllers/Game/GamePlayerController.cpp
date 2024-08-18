// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "../../HUD/Game/HUDGame.h"
#include "../../Components/Artifacts/BaseArtifactComponent.h"
#include "../../InstanceGame.h"
#include "../../Characters/MainCharacter/MainPaperCharacter.h"
#include "../../Data/Enums/ESlotArtifact.h"
#include "../../Data/DataAssets/ArtifactUsedDataAsset.h"

#include <Kismet/GameplayStatics.h>
#include <Blueprint/UserWidget.h>
#include <GameFramework/CharacterMovementComponent.h>





AGamePlayerController::AGamePlayerController()
{
	HUD = nullptr;
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

void AGamePlayerController::SetIconArtifact(const ESlotArtifact slot, UTexture2D* texture)
{
	if (slot == ESlotArtifact::LEFT_SLOT)
	{
		activeArtifacts->leftArtifact.icon = texture;
	}
	else
	{
		activeArtifacts->rightArtifact.icon = texture;
	}
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

void AGamePlayerController::EnableCharacterMovement()
{
	GetCharacter()->GetCharacterMovement()->Activate();
}

void AGamePlayerController::DisableCharacterMovement()
{
	GetCharacter()->GetCharacterMovement()->Deactivate();
}
