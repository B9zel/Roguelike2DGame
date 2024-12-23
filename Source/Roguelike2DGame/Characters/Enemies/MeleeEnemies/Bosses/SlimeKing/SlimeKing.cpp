// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeKing.h"
#include "../../../../../Components/HealthManaComponent/HealthComponent.h"
#include "../../../../../Data/Enums/EBossStage.h"

#include <PaperZD/Public/PaperZDAnimInstance.h>
#include <PaperFlipbookComponent.h>
#include <GameFramework/CharacterMovementComponent.h>





ASlimeKing::ASlimeKing()
{
	PrimaryActorTick.bCanEverTick = true;
	m_CurrentStage = EBossStage::FIRST_STAGE;
}


void ASlimeKing::BeginPlay()
{
	Super::BeginPlay();

	healthComponent->takeDamageDelegate.AddDynamic(this, &ASlimeKing::OnTakeDamage);
	switchStage.Broadcast(EBossStage::FIRST_STAGE);
}

void ASlimeKing::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ASlimeKing::OnAttack()
{
	Super::OnAttack();

	GetAnimInstance()->JumpToNode(Animations.Attack);
}

void ASlimeKing::OnDeath_Implementation(AActor* deadActor, AActor* InstigatorActor)
{
	Super::OnDeath_Implementation(deadActor, InstigatorActor);

	if (deadActor == this)
	{
		GetAnimInstance()->JumpToNode(Animations.Death);
		GetCharacterMovement()->Deactivate();
	}
}

void ASlimeKing::OnTakeDamage(AActor* damageActor)
{
	if (!IsAttacking())
	{
		GetAnimInstance()->JumpToNode(Animations.TakeHit);
	}

	float scale = static_cast<float>(GetHealthComponent()->GetCurrentHP()) / GetHealthComponent()->GetMaxHP();
	if (scale <= HPPercentThirdStage && m_CurrentStage != EBossStage::THIRD_STAGE)
	{
		m_CurrentStage = EBossStage::FIRST_STAGE;
		switchStage.Broadcast(EBossStage::THIRD_STAGE);
	}
	else if (scale <= HPPercentSecondStage && m_CurrentStage != EBossStage::SECOND_STAGE)
	{
		m_CurrentStage = EBossStage::SECOND_STAGE;
		switchStage.Broadcast(EBossStage::SECOND_STAGE);
	}
}

const EBossStage& ASlimeKing::GetCurrentStageBoss()
{
	return m_CurrentStage;
}

float ASlimeKing::GetHPPercentSecondStage()
{
	return HPPercentSecondStage;
}

float ASlimeKing::GetHPPercentThirdStage()
{
	return HPPercentThirdStage;
}

float ASlimeKing::GetSpeedMoveThirdStage()
{
	return SpeedMoveThirdStage;
}

float ASlimeKing::GetSpeedAttackThirdStage()
{
	return SpeedAttackThirdStage;
}

float ASlimeKing::GetSpeedMoveSecondStage()
{
	return SpeedMoveSecondStage;
}

float ASlimeKing::GetSpeedAttackSecondStage()
{
	return SpeedAttackSecondStage;
}
