// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include <Kismet/KismetSystemLibrary.h>


void AMainGameMode::OnDeathActor(AActor* deadActor)
{
	deathDeligate.Broadcast(deadActor);
}


void AMainGameMode::OnSpawnActor(AActor* spawnActor)
{
	spawnDeligate.Broadcast(spawnActor);
}