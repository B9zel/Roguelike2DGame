// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArtifactComponent.h"

UBaseArtifactComponent::UBaseArtifactComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	canUse = true;
	timeReload = 1.0f;
}

bool UBaseArtifactComponent::GetCanUse()
{
	return canUse;
}

float UBaseArtifactComponent::GetTimeReload()
{
	return timeReload;
}

void UBaseArtifactComponent::Interact_Implementation(AActor* interactiveActor)
{
	if (GetCanUse())
	{
		canUse = false;

		FTimerHandle reloadHandle;
		GetWorld()->GetTimerManager().SetTimer(reloadHandle, this, &UBaseArtifactComponent::Reload, GetTimeReload(), false);
	}
}

void UBaseArtifactComponent::Reload()
{
	canUse = true;
}


