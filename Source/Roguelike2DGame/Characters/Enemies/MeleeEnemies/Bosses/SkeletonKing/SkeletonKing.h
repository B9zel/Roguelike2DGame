// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../MeleeEnemy.h"
#include "SkeletonKing.generated.h"



class ASkeletonEnemy;


UCLASS()
class ROGUELIKE2DGAME_API ASkeletonKing : public AMeleeEnemy
{
	GENERATED_BODY()
public:
	ASkeletonKing();
	
protected:
	UFUNCTION(BlueprintCallable)
	ASkeletonEnemy* SpawnSkeletMinion();

	virtual void OnDeath_Implementation(AActor* deadActor, AActor* Instigator) override;

private:
	UFUNCTION()
	void OnDeathSkeletonMinion(AActor* deadActor, AActor* instigatorActor);

protected:

	UPROPERTY(EditAnywhere)
	float timeSpawnSkeletons;
	UPROPERTY(EditAnywhere)
	int maxSkeletons;
	UPROPERTY(EditAnywhere)
	float timeBirth;

	int currenSkeletons;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASkeletonEnemy> skeletonClass;
};
