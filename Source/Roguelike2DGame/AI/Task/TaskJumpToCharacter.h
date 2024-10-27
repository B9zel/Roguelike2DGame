// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "TaskJumpToCharacter.generated.h"



class ASkeletonKingAIController;


UCLASS()
class ROGUELIKE2DGAME_API UTaskJumpToCharacter : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:

	UTaskJumpToCharacter();

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UFUNCTION()
	void LandedOwner(const FHitResult& Hit);

public:

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CharacterToKey;

	UPROPERTY(EditAnywhere)
	float JumpForce;
	UPROPERTY(EditAnywhere)
	float JumpHeight;

	UPROPERTY(EditAnywhere, meta = (ClampMin='0', ClapmMax="1.0"))
	float JumpZDirection;

private:

	ASkeletonKingAIController* owningController;
	ACharacter* ownerCharacter;

	bool isLanded = true;
	bool canJump = true;
	bool isBind = false;
};
