// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtectiveVortexComponent.h"

void UProtectiveVortexComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
}

void UProtectiveVortexComponent::Interact_Implementation(AActor* interactiveActor)
{
	UE_LOG(LogTemp, Warning, TEXT("interact"));
}

void UProtectiveVortexComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UE_LOG(LogTemp, Warning, TEXT("EndPlay"));
}
