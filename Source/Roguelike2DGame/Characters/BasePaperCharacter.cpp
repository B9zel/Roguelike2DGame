// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"
#include "../Components/HealthManaComponent/HealthManaComponent.h"
#include "../GameModes/Game/MainGameMode.h"

#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>




ABasePaperCharacter::ABasePaperCharacter()
{
	healthComponent = CreateDefaultSubobject<UHealthManaComponent>(TEXT("Health and Mana component"));
	healthComponent->takeDamageDelegate.AddDynamic(this, &ABasePaperCharacter::OnTakePlayerDamage);
	//healthComponent->RegisterComponent();

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

UHealthManaComponent* ABasePaperCharacter::GetHealthComponent()
{
	return healthComponent;
}

TArray<TEnumAsByte<EObjectTypeQuery>>& ABasePaperCharacter::GetTargetEnumsObject()
{
	return targetEnums;
}

void ABasePaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	AMainGameMode* gameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this));
	gameMode->deathDeligate.AddDynamic(this, &ABasePaperCharacter::OnDeath);
	gameMode->spawnDeligate.AddDynamic(this, &ABasePaperCharacter::OnSpawn);

	gameMode->OnSpawnActor(this);
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

void ABasePaperCharacter::OnTakePlayerDamage(AActor* instigatorDamage)
{
}

void ABasePaperCharacter::OnDeath(AActor* deadActor)
{
}

void ABasePaperCharacter::OnSpawn(AActor* deadActor)
{
}

