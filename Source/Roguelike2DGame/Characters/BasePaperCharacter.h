// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BasePaperCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseCharacterDelegateWithoutParam);


UCLASS()
class ROGUELIKE2DGAME_API ABasePaperCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

	ABasePaperCharacter();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsAttacking();
	UFUNCTION(BlueprintCallable)
	void SetIsAttacking(bool attack);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class UHealthComponent* GetHealthComponent();

protected:

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	virtual void OnAttack();
	UFUNCTION(BlueprintCallable)
	virtual void OnAttackHit();
	UFUNCTION(BlueprintCallable)
	virtual void OnReloadAttack();
	UFUNCTION(BlueprintCallable)
	virtual void OnEndAttack();
	UFUNCTION()
	virtual void OnTakeDamage(AActor* instigatorDamage);

	UFUNCTION()
	virtual void OnDeath(AActor* deadActor);
protected:

	UPROPERTY(EditAnywhere)
	class UHealthComponent* healthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeReloadAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool canAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float distanceAttack;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> targetEnums;

	FTimerHandle attackReloadTimer;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FBaseCharacterDelegateWithoutParam endAttack;
	UPROPERTY(BlueprintAssignable)
	FBaseCharacterDelegateWithoutParam reloadAttack;
};
