// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../MeleeEnemy.h"
#include "SlimeKing.generated.h"



enum class EBossStage : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSwitchStage, const EBossStage&, Stage);


USTRUCT(BlueprintType)
struct FSlimeKingAnimations
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FName Death;
	UPROPERTY(EditAnywhere)
	FName Attack;
	UPROPERTY(EditAnywhere)
	FName TakeHit;
};


UCLASS()
class ROGUELIKE2DGAME_API ASlimeKing : public AMeleeEnemy
{
	GENERATED_BODY()
	
public:

	ASlimeKing();

public:

	UFUNCTION(BlueprintPure)
	const EBossStage& GetCurrentStageBoss();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void OnAttack() override;
	virtual void OnDeath_Implementation(AActor* deadActor, AActor* InstigatorActor) override;

	UFUNCTION(BlueprintPure)
	float GetHPPercentSecondStage();
	UFUNCTION(BlueprintPure)
	float GetHPPercentThirdStage();

	UFUNCTION(BlueprintPure)
	float GetSpeedMoveThirdStage();
	UFUNCTION(BlueprintPure)
	float GetSpeedAttackThirdStage();
	UFUNCTION(BlueprintPure)
	float GetSpeedMoveSecondStage();
	UFUNCTION(BlueprintPure)
	float GetSpeedAttackSecondStage();

private:

	UFUNCTION()
	void OnTakeDamage(AActor* damageActor);

public:

	UPROPERTY(BlueprintAssignable)
	FSwitchStage switchStage;
	
private:

	UPROPERTY(EditAnywhere)
	FSlimeKingAnimations Animations;

	EBossStage m_CurrentStage;

	UPROPERTY(EditAnywhere)
	float SpeedMoveThirdStage;
	UPROPERTY(EditAnywhere)
	float SpeedAttackThirdStage;
	UPROPERTY(EditAnywhere)
	float SpeedMoveSecondStage;
	UPROPERTY(EditAnywhere)
	float SpeedAttackSecondStage;

	UPROPERTY(EditAnywhere, meta=(ClamoMin="0", ClampMax="1"))
	float HPPercentSecondStage;
	UPROPERTY(EditAnywhere, meta = (ClamoMin = "0", ClampMax = "1"))
	float HPPercentThirdStage;
};
