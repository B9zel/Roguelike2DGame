// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskStepBack.h"
#include <AIController.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <Blueprint/AIAsyncTaskBlueprintProxy.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/Character.h>
#include <Components/CapsuleComponent.h>
#include <Kismet/KismetSystemLibrary.h>





EBTNodeResult::Type UTaskStepBack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwningController = OwnerComp.GetAIOwner();
	Owner = OwnerComp.GetAIOwner()->GetCharacter();

	if (!OwningController || !Owner) return EBTNodeResult::Failed;


	FHitResult ResultTrace;
	TArray<TEnumAsByte<EObjectTypeQuery>> collision = { TEnumAsByte<EObjectTypeQuery>(ECollisionChannel::ECC_WorldStatic) };

	const FVector directionMove = Owner->GetActorLocation() + (-Owner->GetActorForwardVector() * Distance);

	UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Owner->GetActorLocation(), directionMove, collision, false, TArray<AActor*>(),
																							EDrawDebugTrace::ForDuration, ResultTrace, true);
	
	UAIAsyncTaskBlueprintProxy* TaskProxy = UAIBlueprintHelperLibrary::CreateMoveToProxyObject(GetWorld(), Owner, ResultTrace.TraceEnd,nullptr, 5, true);
	TaskProxy->OnSuccess.AddDynamic(this, &UTaskStepBack::FinishMove);
	TaskProxy->OnFail.AddDynamic(this, &UTaskStepBack::FinishMove);
	
	DefaultSpeed = Owner->GetCharacterMovement()->MaxWalkSpeed;
	Owner->GetCharacterMovement()->MaxWalkSpeed = SpeedRetreat;


	return EBTNodeResult::InProgress;
}

void UTaskStepBack::FinishMove(EPathFollowingResult::Type MovementResult)
{
	Owner->GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	FinishLatentTask(*Cast<UBehaviorTreeComponent>(OwningController->GetBrainComponent()), EBTNodeResult::Succeeded);
}