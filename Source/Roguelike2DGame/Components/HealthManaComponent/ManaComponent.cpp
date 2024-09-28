
#include "ManaComponent.h"



UManaComponent::UManaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UManaComponent::BeginPlay()
{
	Super::BeginPlay();

	if (currentMana > maxMana)
	{
		currentMana = maxMana;
	}
}

void UManaComponent::SetMaxMana(int newMax)
{
	if (newMax < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't set max mana: %d"), newMax);
		return;
	}
	maxMana = newMax;
}

int UManaComponent::GetMaxMana()
{
	return maxMana;
}

void UManaComponent::SetMana(int newMana)
{
	if (newMana < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't set mana: %d"), newMana);
		return;
	}
	currentMana = newMana;
	changeManaDelegate.Broadcast();
}

int UManaComponent::GetMana()
{
	return currentMana;
}


