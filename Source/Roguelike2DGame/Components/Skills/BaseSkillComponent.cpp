// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSkillComponent.h"

// Sets default values for this component's properties
UBaseSkillComponent::UBaseSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;


	SetAutoActivate(false);
}


// Called when the game starts
void UBaseSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

