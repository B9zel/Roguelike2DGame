// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"


class AHUDGame;

USTRUCT(BlueprintType)
struct FArtifactUsed
{
	GENERATED_BODY()

	class UBaseArtifactComponent* leftArtifactComponent;

	class UBaseArtifactComponent* rightArtifactComponent;
};


UCLASS()
class ROGUELIKE2DGAME_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	AGamePlayerController();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetMoney();

	UFUNCTION(BlueprintCallable)
	void SetMoney(int32 newMoney);

	UFUNCTION(BlueprintCallable)
	void AddMoney(int32 addMoney);

protected:

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* newPawn) override;

protected:

	AHUDGame* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
	int32 money;

	FArtifactUsed artifactUsed;

};
