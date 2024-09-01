// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "../../InstanceGame.h"
#include "../../Data/ResourceLoader.h"

#include <Kismet/KismetSystemLibrary.h>



void AMainGameMode::OnDeathActor(AActor* deadActor, AActor* InstigatorActor)
{
	deathDeligate.Broadcast(deadActor, InstigatorActor);
}


void AMainGameMode::OnSpawnActor(AActor* spawnActor)
{
	spawnDeligate.Broadcast(spawnActor);
}

void AMainGameMode::EndPlay(EEndPlayReason::Type ReasonEndPlay)
{
	GetGameInstance<UInstanceGame>()->GetResourceLoader()->ClearData();
}
