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
	// Sets default values for this component's properties
	UHealthComponent();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetCurrentHP();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetMaxHP();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere)
	int maxHealth;
	UPROPERTY(EditAnywhere)
	int currentHealth;

	bool isDead;

public:

	FHealthComponentDelegateOneParam takeDamageDelegate;
};
