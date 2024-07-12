// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"


class AHUDGame;
class UArtifactUsedDataAsset;


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


	UFUNCTION(BlueprintCallable)
	UBaseArtifactComponent* BindArtifact(const ESlotArtifact slot,const TSoftClassPtr<UBaseArtifactComponent> artifactBind);

	UFUNCTION(BlueprintCallable)
	void SetIconArtifact(const ESlotArtifact slot, UTexture2D* texture);

	UArtifactUsedDataAsset* GetArtifactDataAsset() { return activeArtifacts; }

protected:

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* newPawn) override;

protected:

	AHUDGame* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
	int32 money;

	UPROPERTY(EditAnywhere)
	UArtifactUsedDataAsset* activeArtifacts;
};
