// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "../../Characters/BasePaperCharacter.h"
#include "../../GameModes/Game/MainGameMode.h"
#include <Kismet/GameplayStatics.h>



// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	maxHealth = 100;
	currentHealth = maxHealth;

	isDead = false;
}

int32 UHealthComponent::GetCurrentHP()
{
	return currentHealth;
}

int32 UHealthComponent::GetMaxHP()
{
	return maxHealth;
}

bool UHealthComponent::GetIsDead()
{
	return isDead;
}

void UHealthComponent::SetCurrentHP(int32 newHP)
{
	if (newHP < 0)
	{
		currentHealth = 0;
	}
	else
	{
		currentHealth = newHP;
	}
}

void UHealthComponent::SetMaxHP(int32 newMax)
{
	if (newMax < currentHealth)
	{
		maxHealth = currentHealth;
	}
	else
	{
		maxHealth = newMax;
	}
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner<ABasePaperCharacter>()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnPlayerTakeAnyDamage);
}


void UHealthComponent::OnPlayerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	currentHealth = FMath::Clamp(currentHealth - Damage, 0, maxHealth);
	takeDamageDelegate.Broadcast(DamagedActor);
	
	if (currentHealth == 0 && !isDead)
	{
		isDead = true;
		Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this))->OnDeathActor(GetOwner());
	}
}

