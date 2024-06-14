// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthManaComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthManaComponentDelegateOneParam, AActor*, instigatorDamage);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKE2DGAME_API UHealthManaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthManaComponent();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetCurrentHP();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetMaxHP();

	bool GetIsDead();

	void SetCurrentHP(int32 newHP);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


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
	FHealthManaComponentDelegateOneParam takeDamageDelegate;
};
