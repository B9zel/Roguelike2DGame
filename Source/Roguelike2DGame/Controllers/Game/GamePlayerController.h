// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"


class AHUDGame;
class UArtifactUsedDataAsset;
class SWidget;



UCLASS()
class ROGUELIKE2DGAME_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AGamePlayerController();

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetMoney() const { return money; }

	UFUNCTION(BlueprintCallable)
	void SetMoney(const int32 newMoney);
	UFUNCTION(BlueprintCallable)
	void AddMoney(const int32 addMoney);


	UFUNCTION(BlueprintCallable)
	UBaseArtifactComponent* BindArtifact(const ESlotArtifact slot,const TSoftClassPtr<UBaseArtifactComponent>& artifactBind);

	UFUNCTION(BlueprintCallable)
	void SetIconArtifact(const ESlotArtifact slot, UTexture2D* texture);

	UFUNCTION(BlueprintCallable)
	void SetInputUIMode(UUserWidget* focusWidget);

	UFUNCTION(BlueprintCallable)
	void SetInputGameMode();

	UFUNCTION(BlueprintCallable)
	void EnableCharacterMovement();
	UFUNCTION(BlueprintCallable)
	void DisableCharacterMovement();

	UArtifactUsedDataAsset* GetArtifactDataAsset() { return activeArtifacts; }

protected:

	virtual void OnPossess(APawn* newPawn) override;

protected:

	UPROPERTY()
	AHUDGame* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
	int32 money;

	UPROPERTY(EditAnywhere)
	UArtifactUsedDataAsset* activeArtifacts;
};
