// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>


AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = false;

	boxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	boxCollision->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnBeginOverlap);
	SetRootComponent(boxCollision);
	
	projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement"));
}

void AArrow::SetDamage(int newDamage)
{
	damage = newDamage < 0 ? 0 : newDamage;
}

int AArrow::GetDamage()
{
	return damage;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArrow::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TSubclassOf<UDamageType> damageType;
	UGameplayStatics::ApplyDamage(OtherActor, GetDamage(), GetInstigatorController(), GetInstigator(), damageType);
	Destroy();
}
