// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonKing.h"
#include "../../Skeletons/SkeletonEnemy.h"
#include "../../../../../Controllers/Game/AI/Melee/BaseMeleeAIController.h"
#include "../../../../../GameModes/Game/MainGameMode.h"
#include <Kismet/GameplayStatics.h>



ASkeletonKing::ASkeletonKing(const FObjectInitializer& OI) : Super(OI)
{
	timeSpawnSkeletons = 10.f;

	maxSkeletons = 5;
	currenSkeletons = 0;
}

void ASkeletonKing::SpawnSkeletMinion()
{
	ASkeletonEnemy* character = GetWorld()->SpawnActor<ASkeletonEnemy>(skeletonClass, GetActorLocation(), FRotator(0, 0, 0));
	character->GetController<ABaseMeleeAIController>()->SetIsImmediatelyAttack(true);
	Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this))->deathDeligate.AddDynamic(this, &ASkeletonKing::OnDeathSkeletonMinion);
	currenSkeletons++;

}

void ASkeletonKing::OnDeathSkeletonMinion(AActor* deadActor)
{
	if (deadActor->StaticClass() == ASkeletonEnemy::StaticClass())
	{
		currenSkeletons--;
	}
}
