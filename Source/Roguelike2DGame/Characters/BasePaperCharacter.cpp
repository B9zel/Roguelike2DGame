// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"
#include "../Components/HealthManaComponent/HealthComponent.h"
#include "../Components/Stat/CharacterStatsComponent.h"
#include "../GameModes/Game/MainGameMode.h"

#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>




ABasePaperCharacter::ABasePaperCharacter()
{
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	healthComponent->takeDamageDelegate.AddDynamic(this, &ABasePaperCharacter::OnTakePlayerDamage);
	
	statsComponent = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("Stat component"));

	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
}


void ABasePaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	AMainGameMode* gameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this));
	gameMode->deathDeligate.AddDynamic(this, &ABasePaperCharacter::OnDeath);
	gameMode->spawnDeligate.AddDynamic(this, &ABasePaperCharacter::OnSpawn);

	gameMode->OnSpawnActor(this);
}

void ABasePaperCharacter::OnReloadAttack()
{
	statsComponent->SetCanAttack(true);
	reloadAttack.Broadcast();
}

void ABasePaperCharacter::OnEndAnimAttack()
{
	endAnimAttack.Broadcast();
}
