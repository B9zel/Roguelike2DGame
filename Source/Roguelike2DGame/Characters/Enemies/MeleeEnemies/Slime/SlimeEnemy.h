// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MeleeEnemy.h"
#include "SlimeEnemy.generated.h"


USTRUCT(BlueprintType)
struct FSlimeAnimation
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
class ROGUELIKE2DGAME_API ASlimeEnemy : public AMeleeEnemy
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure)
	float GetRunSpeed();
	UFUNCTION(BlueprintPure)
	float GetWalkSpeed();

protected:

	virtual void BeginPlay() override;
	virtual void OnAttack() override;
	virtual void OnDeath_Implementation(AActor* deadActor, AActor* Instigator) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:

	UPROPERTY(EditAnywhere)
	FSlimeAnimation Animations;

	UPROPERTY(EditAnywhere, meta=(ClampUI="0.0", UIMin="0.0"))
	float walkSpeed;
	UPROPERTY(EditAnywhere, meta=(ClampUI="0.0", UIMin="0.0"))
	float runSpeed;
};
