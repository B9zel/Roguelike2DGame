// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthComponentDelegateOneParam, AActor*, instigatorDamage);




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKE2DGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();

public:

	UFUNCTION(BlueprintPure)
	int32 GetCurrentHP();
	UFUNCTION(BlueprintPure)
	int32 GetMaxHP();
	UFUNCTION(BlueprintPure)
	bool GetIsDead();

	void SetCurrentHP(int32 newHP);
	void SetMaxHP(int32 newMax);

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

protected:

	UPROPERTY(EditAnywhere)
	int32 maxHealth;
	UPROPERTY(EditAnywhere)
	int32 currentHealth;

	bool isDead;

public:

	UPROPERTY(BlueprintAssignable)
	FHealthComponentDelegateOneParam takeDamageDelegate;
};
