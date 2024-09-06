// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseWeapon.generated.h"


#define CHECK_WITH_LOG_WARNING(CheckIs, Text) {  \
			if (CheckIs) {UE_LOG(LogTemp, Warning, TEXT(Text)); return; \
			}}

class ABasePaperCharacter;
class ULevelConfigDataAsset;
enum class EWeaponType : uint8;


UCLASS(Abstract, Blueprintable)
class ROGUELIKE2DGAME_API UBaseWeapon : public UObject
{
	GENERATED_BODY()

public:

	UBaseWeapon();

public:

	virtual void PostInitProperties() override;

	
	UFUNCTION(BlueprintCallable)
	virtual bool DamageLevelUp();
	UFUNCTION(BlueprintCallable)
	virtual bool SpeedAttackLevelUp();

	
	// Getters
	UFUNCTION(BlueprintPure)
	virtual float GetTimeReload()					{ return 0; }

	UFUNCTION(BlueprintPure)
	bool GetCanAttack() const						{ return canAttack; }
	
	UFUNCTION(BlueprintPure)
	bool IsAttacking() const						{ return isAttacking; }
	UFUNCTION(BlueprintPure)
	bool IsReady() const							{ return isReady; }
	UFUNCTION(BlueprintPure)
	int GetSouls() const							{ return soulsCurrent; }
	UFUNCTION(BlueprintPure)
	int GetLevelDamage() const						{ return currentLevelDamage; }
	UFUNCTION(BlueprintPure)
	int GetLevelSpeedAttack() const					{ return currentLevelSpeedAttack; }
	UFUNCTION(BlueprintPure)
	ABasePaperCharacter* GetOwner() const			{ return owner; }
	UFUNCTION(BlueprintPure)
	const EWeaponType& GetWeaponType() const		{ return weaponType; }
	UFUNCTION(BlueprintPure)
	int GetDamage() const							{ return damage; }
	UFUNCTION(BlueprintPure)
	ULevelConfigDataAsset* GetConfigLevelOfWeapon() { return configLevel; }
	UFUNCTION(BlueprintPure)
	int GetMaxLevel() const;
	UFUNCTION(BlueprintPure)
	int GetSoulsMaxForDamage() const;
	UFUNCTION(BlueprintPure)
	int GetSoulsMaxForAttackSpeed() const;
	UFUNCTION(BlueprintPure)
	int GetGoldsMaxForDamage() const;
	UFUNCTION(BlueprintPure)
	int GetGoldsMaxForAttackSpeed() const;


	// Setters
	UFUNCTION()
	void SetOwner(ABasePaperCharacter* character) { owner = character; }
	UFUNCTION(BlueprintCallable)
	void SetCanAttack(const bool can)			  { canAttack = can; }
	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(const bool is)			  { isAttacking = is; }

	UFUNCTION(BlueprintCallable)
	void SetIsReady(const bool is)				  { isReady = is; }
	UFUNCTION(BlueprintCallable)
	void SetSouls(const int souls);
	UFUNCTION(BlueprintCallable)
	void SetLevelDamage(const int level);
	UFUNCTION(BlueprintCallable)
	void SetLeveSpeedAttack(const int level);
	UFUNCTION()
	void SetDamage(const int newDamage);

	//UFUNCTION(BlueprintCallable)
	virtual void SetTimeReload(const float time) PURE_VIRTUAL(UBaseWeapon::SetTimeReload, );


	UFUNCTION(BlueprintCallable)
	void AddSouls(const int count);

protected:

	virtual void FinishReload();

protected:

	UPROPERTY()
	EWeaponType weaponType;
	UPROPERTY()
	ABasePaperCharacter* owner;
	
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> typesAttackCollision; // types of collision, that can be attacked
	UPROPERTY()
	FTimerHandle reloadHandle;

	//Attack
	UPROPERTY(EditAnywhere)
	bool canAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", UIMin = "0"))
	int damage;
	bool isAttacking;
	bool isReady;


	// Soul
	UPROPERTY(EditAnywhere, meta=(ClampMin="0", UIMin="0"))
	int soulsCurrent;

	// Level
	UPROPERTY(EditAnywhere, meta=(ClampMin="1", UIMin="1"))
	int currentLevelDamage;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", UIMin = "1"))
	int currentLevelSpeedAttack;

	UPROPERTY(EditAnywhere)
	ULevelConfigDataAsset* configLevel;

	// Value, that change damage
	UPROPERTY(EditAnywhere)
	float levelUpDamage;

};