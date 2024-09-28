// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"
#include "../Components/HealthManaComponent/HealthComponent.h"
#include "../Components/Stat/CharacterStatsComponent.h"
#include "../GameModes/Game/MainGameMode.h"

#include <GameFramework/CharacterMovementComponent.h>
#include <PaperZDAnimInstance.h>
#include <Kismet/GameplayStatics.h>




ABasePaperCharacter::ABasePaperCharacter()
{
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	
	statsComponent = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("Stat component"));

	//Restriction on movement along the Y axis
	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);

	m_bufferMovementMode = GetCharacterMovement()->MovementMode;
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
	reloadAttack.Broadcast();
}

void ABasePaperCharacter::OnEndAnimAttack()
{
	endAnimAttack.Broadcast();
}

void ABasePaperCharacter::EnableCharacterMovement()
{
	//GetCharacterMovement()->SetMovementMode(m_bufferMovementMode);
	GetCharacterMovement()->Activate();
}

void ABasePaperCharacter::DisableCharacterMovement() 
{	 
	//m_bufferMovementMode = GetCharacterMovement()->MovementMode;
	//GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->Deactivate();
}

void ABasePaperCharacter::PlayAnimation(FName nameAnim)
{
	GetAnimInstance()->JumpToNode(nameAnim);
}