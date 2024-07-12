// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterStatsComponent.h"
#include "../../Characters/BasePaperCharacter.h"




UCharacterStatsComponent::UCharacterStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
	timeReloadAttack = 0.1f;
	isAttacking = false;
	canAttack = true;
}

void UCharacterStatsComponent::SetIsAttacking(bool attack)
{
	this->isAttacking = attack;
}


void UCharacterStatsComponent::SetTimeReloadAttack(float time)
{
	timeReloadAttack = time < 0.0f ? 0.0f : time;
}
