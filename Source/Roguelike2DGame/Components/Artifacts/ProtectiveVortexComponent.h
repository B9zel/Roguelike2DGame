// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseArtifactComponent.h"
#include "../../Data/ResourceLoader.h"
#include "ProtectiveVortexComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ROGUELIKE2DGAME_API UProtectiveVortexComponent : public UBaseArtifactComponent
{
	GENERATED_BODY()

protected:

	virtual void Interact_Implementation(AActor* interactiveActor) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
protected:

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AActor> ProtectedField;

private:

	LoaderHandle loadFieldHandle;

};
