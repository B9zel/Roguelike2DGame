// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseArtifactComponent.h"
#include "../../Interfaces/InteractInterface.h"
#include "ProtectiveVortexComponent.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API UProtectiveVortexComponent : public UBaseArtifactComponent, public IInteract
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	virtual void Interact_Implementation(AActor* interactiveActor) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:

	UPROPERTY(EditAnywhere)
	float powerImpulse;
	UPROPERTY(EditAnywhere)
	float radius;
	
};
