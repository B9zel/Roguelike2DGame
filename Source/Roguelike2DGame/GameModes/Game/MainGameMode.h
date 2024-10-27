// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMainGameModeDelegateTwoParam, AActor*, actor, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMainGameModeDelegateOneParam, AActor*, actor);


UCLASS()
class ROGUELIKE2DGAME_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

	void OnDeathActor(AActor* deadActor, AActor* Instigator);
	void OnSpawnActor(AActor* spawnActor);

protected:

	virtual void EndPlay(EEndPlayReason::Type ReasonEndPlay) override;

public:
	
	UPROPERTY(BlueprintAssignable)
	FMainGameModeDelegateTwoParam deathDeligate;
	UPROPERTY(BlueprintAssignable)
	FMainGameModeDelegateOneParam spawnDeligate;
};
