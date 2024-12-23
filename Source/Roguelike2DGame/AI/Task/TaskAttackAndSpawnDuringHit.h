// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "TaskAttackAndSpawnDuringHit.generated.h"



class AEnemyCharacter;


UCLASS()
class ROGUELIKE2DGAME_API UTaskAttackAndSpawnDuringHit : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


private:

	UFUNCTION()
	void EndAttack();
	UFUNCTION()
	void HitAttack();

protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> Spawn;

private:

	AEnemyCharacter* OwningCharacter;
};
