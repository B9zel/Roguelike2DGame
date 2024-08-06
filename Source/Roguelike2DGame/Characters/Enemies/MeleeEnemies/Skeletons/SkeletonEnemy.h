// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MeleeEnemy.h"
#include "SkeletonEnemy.generated.h"



USTRUCT(BlueprintType)
struct FSkeletonAnimation
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, Category = "Anim")
	FName death;

	UPROPERTY(EditAnywhere, Category = "Anim")
	FName takeDamage;

	UPROPERTY(EditAnywhere, Category = "Anim")
	FName attack;

};

UCLASS()
class ROGUELIKE2DGAME_API ASkeletonEnemy : public AMeleeEnemy
{
	GENERATED_BODY()
public:

	ASkeletonEnemy();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;

	virtual void OnAttack() override;

	virtual void OnReloadAttack() override;

	virtual void OnDeath(AActor* deadActor, AActor* Instigator) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	void Destroyer();

protected:

	UPROPERTY(EditAnywhere)
	float timeDestroyAfterDeath;

	UPROPERTY(EditAnywhere)
	FSkeletonAnimation anim;

};
