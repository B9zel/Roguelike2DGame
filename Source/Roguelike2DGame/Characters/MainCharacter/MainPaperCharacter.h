// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BasePaperCharacter.h"
#include "MainPaperCharacter.generated.h"



USTRUCT(BlueprintType)
struct FCharacterInputAction
{
	GENERATED_BODY()


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
};



UCLASS()
class ROGUELIKE2DGAME_API AMainPaperCharacter : public ABasePaperCharacter
{
	GENERATED_BODY()

public:

	AMainPaperCharacter();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsDashing();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetMoney();

	UFUNCTION(BlueprintCallable)
	void SetMoney(int32 newMoney);

	UFUNCTION(BlueprintCallable)
	void AddMoney(int32 addMoney);

protected:

	virtual void SetupPlayerInputComponent(UInputComponent* inputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;
	
	
	virtual void OnJumped_Implementation() override;

	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;
	
	virtual void RightMove(const struct FInputActionInstance& instance);

	virtual void Dash();

	virtual void OnStopDash();

	virtual void OnReloadDash();

	virtual void LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride) override;

	virtual void OnAttack() override;

	virtual void OnAttackHit() override;

	virtual void OnDeath(AActor* deadActor) override;

	virtual void OnSpawn(AActor* spawnActor) override;
	
	void ToNormalize(float normalizeVal);


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USpringArmComponent* springArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCameraComponent* cameraComponent;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* niagaraSystem;
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* niagaraComponent;

	UPROPERTY(EditAnywhere)
	FCharacterInputAction Input;
	
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float normalizeValues;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin="0"))
	int32 money;

private:

	float m_defoultGravity;
};
