// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"
#include "../Components/HealthComponent/HealthComponent.h"



ABasePaperCharacter::ABasePaperCharacter()
{
	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	

}
