// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "../../Characters/BasePaperCharacter.h"
#include "../../GameModes/Game/MainGameMode.h"
#include <Kismet/GameplayStatics.h>



// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner<ABasePaperCharacter>()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnPlayerTakeAnyDamage);	
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UHealthComponent::OnPlayerTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	currentHealth = FMath::Clamp(currentHealth - Damage, 0, maxHealth);
	takeDamageDelegate.Broadcast(DamagedActor);
	UE_LOG(LogTemp, Warning, TEXT("%f"), currentHealth);
	if (currentHealth == 0)
	{
		Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this))->OnDeathActor(GetOwner());
		
		// Call function "Dead"
	}
}

