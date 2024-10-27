// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskJumpToCharacter.h"
#include "../../Controllers/Game/AI/Melee/SkeletonKingAIController.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/Character.h>
#include <AIController.h>




UTaskJumpToCharacter::UTaskJumpToCharacter()
{
	JumpForce = 1000;
	JumpHeight = 800;
	JumpZDirection = 0.5;

	bNotifyTick = true;
	owningController = nullptr;
	ownerCharacter = nullptr;
}

EBTNodeResult::Type UTaskJumpToCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!isLanded)
	{
		return EBTNodeResult::InProgress;
	}

	ACharacter* characterTo = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(CharacterToKey.SelectedKeyName));
	if (!owningController)
	{
		owningController = Cast<ASkeletonKingAIController>(OwnerComp.GetAIOwner());
	}
	if (!ownerCharacter)
	{
		ownerCharacter = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	}

	if (!ownerCharacter || !characterTo || !owningController)
	{
		return EBTNodeResult::Failed;
	}

	if (!isBind)
	{
		ownerCharacter->LandedDelegate.AddDynamic(this, &UTaskJumpToCharacter::LandedOwner);
		isBind = true;
	}
	
	FVector directionToCharacter = (characterTo->GetActorLocation() - ownerCharacter->GetActorLocation());
	directionToCharacter.Y = 0.0f;
	directionToCharacter.Z *= JumpZDirection;

	FVector Velocity = directionToCharacter.GetSafeNormal() * (directionToCharacter.Length()) + FVector(0.0f, 0.0f, JumpHeight);
	ownerCharacter->LaunchCharacter(Velocity, true, true);
	owningController->JumpSetup();

	isLanded = false;
	canJump = false;

	return EBTNodeResult::InProgress;
}

void UTaskJumpToCharacter::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (isLanded && !canJump)
	{
		canJump = true;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


void UTaskJumpToCharacter::LandedOwner(const FHitResult& Hit)
{
	isLanded = true;
	if (owningController)
	{
		owningController->StopJumpSetup();
	}
}
