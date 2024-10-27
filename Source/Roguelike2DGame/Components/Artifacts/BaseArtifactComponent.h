// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../Interfaces/InteractInterface.h"
#include "BaseArtifactComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKE2DGAME_API UBaseArtifactComponent : public UActorComponent, public IInteract
{
	GENERATED_BODY()

public:	

	UBaseArtifactComponent();

public:

	bool GetCanUse();
	float GetTimeReload();

protected:

	virtual void Interact_Implementation(AActor* interactiveActor) override;

private:

	UFUNCTION()
	void Reload();

protected:

	UPROPERTY(EditAnywhere, meta=(ClampMin="0"))
	float timeReload;
	
	UPROPERTY()
	bool canUse;



};
