// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtifactUsedDataAsset.h"
#include "../../Components/Artifacts/BaseArtifactComponent.h"
#include "../../Data/Enums/ESlotArtifact.h"

#include <Kismet/KismetSystemLibrary.h>




void UArtifactUsedDataAsset::SetIcon(const ESlotArtifact slot, UTexture2D* Texture)
{
	if (!Texture)
	{
		UE_LOG(LOG_ArtifactDataAasset, Warning, TEXT("The texture not valid"));
		return;
	}

	(slot == ESlotArtifact::LEFT_SLOT ? leftArtifact.icon : rightArtifact.icon) = Texture;
}


bool UArtifactUsedDataAsset::FindArtifact(const FString pahtToArtifact, ESlotArtifact& slot)
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *UKismetSystemLibrary::GetPathName(leftArtifact.artifact));
	UE_LOG(LogTemp, Display, TEXT("%s"), *UKismetSystemLibrary::GetPathName(rightArtifact.artifact));
	if (UKismetSystemLibrary::GetPathName(leftArtifact.artifact) == pahtToArtifact)
	{
		slot = ESlotArtifact::LEFT_SLOT;
		return true;
	}
	if (UKismetSystemLibrary::GetPathName(rightArtifact.artifact) == pahtToArtifact)
	{
		slot = ESlotArtifact::RIGHT_SLOT;
		return true;
	}
	return false;
}