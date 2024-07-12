// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMeleeWeapon.h"
#include "../../../../Interfaces/Weapon/MeleeWeapon.h"
#include "Sword.generated.h"




UCLASS()
class ROGUELIKE2DGAME_API USword : public UBaseMeleeWeapon
{
	GENERATED_BODY()
	
public:

	USword();

	virtual void Attack_Implementation() override;

	UFUNCTION(BlueprintCallable)
	float GetDistanceAttack() { return distanceAttack; }

	UFUNCTION(BlueprintCallable)
	int GetDamage() { return damage; }

	void SetDamage(int newDamage);
	void SetDistanceAttack(float distance);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float distanceAttack;

	UPROPERTY(EditAnywhere)
	float capsuleRadiusAttack;
	UPROPERTY(EditAnywhere)
	float capsuleHalfHeightAttack;

};