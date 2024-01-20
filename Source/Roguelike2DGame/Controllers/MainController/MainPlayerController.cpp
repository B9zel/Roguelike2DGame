// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include <Components/InputComponent.h>
#include <EnhancedInputComponent.h>
#include <InputAction.h>
#include <EnhancedInputSubsystems.h>




AMainPlayerController::AMainPlayerController()
{
}



void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* enhuncedInput = Cast< UEnhancedInputComponent>(InputComponent);
//	enhuncedInput->BindAction(,ETriggerEvent::)
}
