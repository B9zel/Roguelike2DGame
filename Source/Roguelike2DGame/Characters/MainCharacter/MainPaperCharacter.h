// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BasePaperCharacter.h"
#include "MainPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API AMainPaperCharacter : public ABasePaperCharacter
{
	GENERATED_BODY()

public:

	AMainPaperCharacter();


protected:

	virtual void SetupPlayerInputComponent(UInputComponent* inputComponent) override;

	virtual void BeginPlay() override;

	
	
	virtual void OnJumped_Implementation() override;

	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;
	
	virtual void RightMove(const struct FInputActionInstance& instance);

	virtual void Dash();

	virtual void OnStopDash();

	virtual void OnReloadDash();

	virtual void LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride) override;

	virtual void OnAttack() override;

	virtual void OnAttackHit() override;

public:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComponent;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* cameraComponent;

protected:

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* actionRun;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* actionJump;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* actionDash;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* actionAttack;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* inputMapping;


	UPROPERTY(EditAnywhere)
	float powerDash;
	UPROPERTY(EditAnywhere)
	float timeDash; 
	UPROPERTY(EditAnywhere)
	float reloadDash;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isDashing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool canDash;

};
