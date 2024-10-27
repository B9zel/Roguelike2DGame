// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../MeleeEnemy.h"
#include "SkeletonKing.generated.h"



class ASkeletonEnemy;
enum class EBossStage : uint8;



UCLASS()
class ROGUELIKE2DGAME_API ASkeletonKing : public AMeleeEnemy
{
	GENERATED_BODY()
public:

	ASkeletonKing();
	
protected:

	virtual void OnDeath_Implementation(AActor* deadActor, AActor* Instigator) override;

	UFUNCTION(BlueprintCallable)
	ASkeletonEnemy* SpawnSkeletMinion();
	UFUNCTION(BlueprintPure)
	EBossStage GetCurrentStage();
	UFUNCTION(BlueprintCallable)
	void SetStage(const EBossStage& newStage);

private:
	UFUNCTION()
	void OnDeathSkeletonMinion(AActor* deadActor, AActor* instigatorActor);

protected:

	EBossStage currentStage;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASkeletonEnemy> skeletonClass;
};
