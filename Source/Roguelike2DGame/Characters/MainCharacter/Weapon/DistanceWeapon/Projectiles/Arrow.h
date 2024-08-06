// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"


class UProjectileMovementComponent;
class UBoxComponent;


UCLASS()
class ROGUELIKE2DGAME_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AArrow();

public:


	void SetDamage(int newDamage);

	int GetDamage();


protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* projectile;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxCollision;

private:

	int damage;
};
