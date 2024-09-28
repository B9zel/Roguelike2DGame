// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonKing.h"
#include "../../Skeletons/SkeletonEnemy.h"
#include "../../../../../Controllers/Game/AI/Melee/BaseMeleeAIController.h"
#include "../../../../../GameModes/Game/MainGameMode.h"
#include <Kismet/GameplayStatics.h>
#include <PaperZDAnimInstance.h>



ASkeletonKing::ASkeletonKing()
{
	timeSpawnSkeletons = 10.f;

	maxSkeletons = 5;
	currenSkeletons = 0;

	
}

void ASkeletonKing::OnDeath_Implementation(AActor* actor, AActor* InstigatorActor)
{
	Super::OnDeath(actor, InstigatorActor);

	if (actor == this)
	{
		DisableInput(GetController<APlayerController>());
		GetAnimInstance()->JumpToNode("Death");
	}
}

ASkeletonEnemy* ASkeletonKing::SpawnSkeletMinion()
{
	ASkeletonEnemy* character = nullptr;
	if (currenSkeletons < maxSkeletons)
	{	

		character = GetWorld()->SpawnActor<ASkeletonEnemy>(skeletonClass, GetActorLocation(), FRotator(0, 0, 0));
		if (character != nullptr)
		{
			//character->GetController<ABaseMeleeAIController>()->SetIsImmediatelyAttack(true);
			Cast<AMainGameMode>(UGameplayStatics::GetGameMode(this))->deathDeligate.AddDynamic(this, &ASkeletonKing::OnDeathSkeletonMinion);
			currenSkeletons++;
		}
	}
	return character;
}

void ASkeletonKing::OnDeathSkeletonMinion(AActor* deadActor, AActor* InstigatorActor)
{
	if (deadActor->StaticClass() == ASkeletonEnemy::StaticClass())
	{
		currenSkeletons--;
	}
}
