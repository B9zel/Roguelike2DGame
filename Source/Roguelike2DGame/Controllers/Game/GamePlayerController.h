// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../../Data/ResourceLoader.h"
#include "GamePlayerController.generated.h"




DECLARE_LOG_CATEGORY_CLASS(GameController, Display, Display)



class AHUDGame;
class UArtifactUsedDataAsset;
class UInputMappingContext;
class UInputAction;


USTRUCT(BlueprintType)
struct FControllerInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UInputAction* inventoryCallAction;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* controllerInputContext;
};



UCLASS()
class ROGUELIKE2DGAME_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AGamePlayerController();

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetGolds() const { return Golds; }
	UFUNCTION(BlueprintPure)
	UArtifactUsedDataAsset* GetArtifactDataAsset();
	UFUNCTION(BlueprintPure)
	int32 GetEnergyOfSouls();

	UFUNCTION(BlueprintCallable)
	void SetGolds(const int32 newGolds);
	UFUNCTION(BlueprintCallable)
	void SetEnergyOfSouls(int32 number);
	UFUNCTION(BlueprintCallable)
	void AddGolds(const int32 addGolds);
	
	UFUNCTION(BlueprintCallable)
	void AddEnergyOfSouls(int32 addValue);


	UFUNCTION(BlueprintCallable)
	UBaseArtifactComponent* BindArtifact(const ESlotArtifact slot,const TSoftClassPtr<UBaseArtifactComponent>& artifactBind);

	UFUNCTION(BlueprintCallable)
	void SetInputUIMode(UUserWidget* focusWidget);
	UFUNCTION(BlueprintCallable)
	void SetInputGameMode();

	UFUNCTION(BlueprintCallable)
	void EnableCharacterMovement();
	UFUNCTION(BlueprintCallable)
	void DisableCharacterMovement();


protected:

	virtual void OnPossess(APawn* newPawn) override;
	virtual void SetupInputComponent() override;

	void OnShowInventory();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin="0"))
	int32 Golds;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", UIMin = "0"))
	int32 energyOfSouls;

	UPROPERTY()
	AHUDGame* HUD;
	UPROPERTY(EditAnywhere)
	FControllerInputAction Input;

private:

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	TSoftObjectPtr<UArtifactUsedDataAsset> activeArtifacts;

	LoaderHandle loaderArtifactAsset;
};
