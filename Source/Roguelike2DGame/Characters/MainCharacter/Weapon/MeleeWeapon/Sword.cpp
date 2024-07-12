// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "../../../BasePaperCharacter.h"
#include "../../../../Data/Enums/EWeaponType.h"


#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>




USword::USword()
{
	weaponType = EWeaponType::SWORD;
	damage = 1;
	distanceAttack = 20;
	capsuleRadiusAttack = 15;
	capsuleHalfHeightAttack = 25;
}

void USword::Attack_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Sword attacl"));
	const TArray<AActor*> actorsIgnore;
	TArray<FHitResult> res;
	TSubclassOf<UDamageType> damageType;

	const FVector actorLocation = GetOwner()->GetActorLocation();

	UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, actorLocation, actorLocation + (GetOwner()->GetActorForwardVector() * GetDistanceAttack()),
		capsuleRadiusAttack, capsuleHalfHeightAttack, Cast<ABasePaperCharacter>(GetOwner())->GetTargetEnumsObject(), false, actorsIgnore, EDrawDebugTrace::ForDuration, res, true);
	
	for (auto& el : res)
	{
		UGameplayStatics::ApplyDamage(el.GetActor(), GetDamage(), GetOwner()->GetInstigatorController(), nullptr, damageType);
	}
}

void USword::SetDistanceAttack(float distance)
{
	distanceAttack = distance < 0.0f ? 0.0f : distance;
}

void USword::SetDamage(int newDamage)
{
	damage = newDamage < 0 ? 0 : newDamage;
}