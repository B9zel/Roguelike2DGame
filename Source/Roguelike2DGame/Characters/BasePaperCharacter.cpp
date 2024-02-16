// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"
#include "../Components/HealthComponent/HealthComponent.h"
#include "../GameModes/Game/MainGameMode.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>




ABasePaperCharacter::ABasePaperCharacter()
{
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	healthComponent->takeDamageDelegate.AddDynamic(this, &ABasePaperCharacter::OnTakeDamage);

	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);

	damage = 1.f;
	timeReloadAttack = 0.1f;
	distanceAttack = 10;
	isAttacking = false;
	canAttack = true;
}

bool ABasePaperCharacter::GetIsAttacking()
{
	return isAttacking;
}

void ABasePaperCharacter::SetIsAttacking(bool attack)
{
	this->isAttacking = attack;
}

UHealthComponent* ABasePaperCharacter::GetHealthComponent()
{
	return healthComponent;
}

void ABasePaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this))->deathDeligate.AddDynamic(this, &ABasePaperCharacter::OnDeath);
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
	reloadAttack.Broadcast();
}

void ABasePaperCharacter::OnEndAttack()
{
	endAttack.Broadcast();
}

void ABasePaperCharacter::OnTakeDamage(AActor* instigatorDamage)
{
}

void ABasePaperCharacter::OnDeath(AActor* deadActor)
{
}

