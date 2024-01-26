// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"
#include "../Components/HealthComponent/HealthComponent.h"



ABasePaperCharacter::ABasePaperCharacter()
{
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	
	damage = 1.f;
	timeReloadAttack = 0.1f;
	distanceAttack = 10;
	isAttacking = false;
	canAttack = true;
}

void ABasePaperCharacter::OnAttack()
{
}

void ABasePaperCharacter::OnAttackHit()
{
}

void ABasePaperCharacter::OnReloadAttack()
{
	canAttack = true;
}

