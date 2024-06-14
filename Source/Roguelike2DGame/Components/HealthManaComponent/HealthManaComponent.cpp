// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthManaComponent.h"
#include "../../Characters/BasePaperCharacter.h"
#include "../../GameModes/Game/MainGameMode.h"
#include <Kismet/GameplayStatics.h>



// Sets default values for this component's properties
UHealthManaComponent::UHealthManaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	maxHealth = 100;
	currentHealth = maxHealth;

	isDead = false;
}

int32 UHealthManaComponent::GetCurrentHP()
{
	return currentHealth;
}

int32 UHealthManaComponent::GetMaxHP()
{
	return maxHealth;
}

bool UHealthManaComponent::GetIsDead()
{
	return isDead;
}

void UHealthManaComponent::SetCurrentHP(int32 newHP)
{
	currentHealth = newHP;
}


// Called when the game starts
void UHealthManaComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner<ABasePaperCharacter>()->OnTakeAnyDamage.AddDynamic(this, &UHealthManaComponent::OnPlayerTakeAnyDamage);
}

// Called every frame
void UHealthManaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


void UHealthManaComponent::OnPlayerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	currentHealth = FMath::Clamp(currentHealth - Damage, 0, maxHealth);
	takeDamageDelegate.Broadcast(DamagedActor);
	//UE_LOG(LogTemp, Error, TEXT("%s %s"), DamagedActor, DamageCauser);
	if (currentHealth == 0 && !isDead)
	{
		isDead = true;
		Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this))->OnDeathActor(GetOwner());
	}
}

