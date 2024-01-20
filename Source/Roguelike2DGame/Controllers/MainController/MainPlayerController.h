// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AMainPlayerController();

protected:
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

protected:

	//TSoftObjectPtr<UInputMappingContext> InputMapping;

};
