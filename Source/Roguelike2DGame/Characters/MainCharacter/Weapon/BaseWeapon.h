// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseWeapon.generated.h"



class ABasePaperCharacter;
enum class EWeaponType : uint8;


UCLASS(Abstract, Blueprintable)
class ROGUELIKE2DGAME_API UBaseWeapon : public UObject
{
	GENERATED_BODY()

public:

	UBaseWeapon();

public:

	virtual void PostInitProperties() override;

	const EWeaponType& GetWeaponType() { return weaponType; }

	void SetOwner(ABasePaperCharacter* character) { owner = character; }
	ABasePaperCharacter* GetOwner() { return owner; }

	virtual void StartReload();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetCanAttack() { return canAttack; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetTimeReload() { return timeReload; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsAttacking() { return isAttacking; }

	UFUNCTION(BlueprintCallable)
	void SetCanAttack(bool can) { canAttack = can; }
	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool is) { isAttacking = is; }
	UFUNCTION(BlueprintCallable)
	void SetTimeReload(float time);

protected:

	virtual void FinishReload();

protected:

	UPROPERTY()
	EWeaponType weaponType;
	UPROPERTY()
	ABasePaperCharacter* owner;

	FTimerHandle reloadHandle;

	// characteristics
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int damage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	float timeReload;

	UPROPERTY(EditAnywhere)
	bool canAttack;

	//UPROPERTY(EditAnywhere)
	bool isAttacking;
};
