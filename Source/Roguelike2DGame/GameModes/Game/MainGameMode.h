// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMainGameModeDelegateOneParam, AActor*, actor);

UCLASS()
class ROGUELIKE2DGAME_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

	void OnDeathActor(AActor* deadActor);

	void OnSpawnActor(AActor* spawnActor);

public:
	FMainGameModeDelegateOneParam deathDeligate;
	FMainGameModeDelegateOneParam spawnDeligate;
};
