// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtectiveVortexComponent.h"
#include <Components/SphereComponent.h>





void UProtectiveVortexComponent::Interact_Implementation(AActor* interactiveActor)
{
	if (GetCanUse())
	{
		if (!loadFieldHandle.IsValid())
		{
			ResourceLoader::ResourceSyncLoad(loadFieldHandle, ProtectedField.ToSoftObjectPath());
		}

		FActorSpawnParameters spawnParam;
		GetWorld()->SpawnActor<AActor>(Cast<UClass>(ResourceLoader::GetData(loadFieldHandle)), GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), spawnParam);
	}
}

void UProtectiveVortexComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}