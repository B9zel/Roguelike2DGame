// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MeleeEnemy.h"
#include "SkeletonEnemy.generated.h"




USTRUCT(BlueprintType)
struct FSkeletonAnimation
{
	GENERATED_BODY()

public:

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

	virtual void OnAttack() override;
	virtual void OnDeath_Implementation(AActor* deadActor, AActor* Instigator) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
protected:

	UPROPERTY(EditAnywhere)
	FSkeletonAnimation anim;
};
