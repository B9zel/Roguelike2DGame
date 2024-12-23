// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbSkillComponent.h"
#include "../../Characters/MainCharacter/MainPaperCharacter.h"

#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>


UClimbSkillComponent::UClimbSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	hasClimb = false;
	isClimbing = false;
	defaultGravity = 0.0f;
}

void UClimbSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	owningCharacter = GetOwner<AMainPaperCharacter>();
	if (owningCharacter)
	{
		owningCharacter->LandedDelegate.AddDynamic(this, &UClimbSkillComponent::OnLanded);
	}
}

void UClimbSkillComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	
	if (!TimerHnd.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHnd, this, &UClimbSkillComponent::CheckClimb, RateCheck <= 0.0f ? UE_KINDA_SMALL_NUMBER : RateCheck, true);
	}
}

void UClimbSkillComponent::Deactivate()
{
	Super::Deactivate();

	if (TimerHnd.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHnd);
	}
}

void UClimbSkillComponent::EnableClimb()
{
	if (owningCharacter)
	{
		owningCharacter->ResetMove();
		defaultGravity = owningCharacter->GetCharacterMovement()->GravityScale;
		owningCharacter->GetCharacterMovement()->GravityScale = FMath::Clamp(GravityOfCharacterDuringClimb, 0.0f, owningCharacter->GetCharacterMovement()->GravityScale);

		hasClimb = true;
		isClimbing = true;
	}
}

void UClimbSkillComponent::DisableClimb()
{
	if (owningCharacter)
	{
		owningCharacter->GetCharacterMovement()->GravityScale = defaultGravity;
		hasClimb = false;
		isClimbing = false;
	}
}

void UClimbSkillComponent::CheckClimb()
{
	FHitResult Result;
	bool isBlock = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * DistanceTrace), 
		CollisionCheck, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, Result, true);

	if (isBlock)
	{
		if (isClimbing || owningCharacter->GetCharacterMovement()->IsWalking() || !owningCharacter->IsCurrentMove()) return;

		EnableClimb();
	}
	else if (isClimbing)
	{
		DisableClimb();
	}
}

void UClimbSkillComponent::OnLanded(const FHitResult& Hit)
{
	if (!isClimbing) return;
	
	DisableClimb();
}

bool UClimbSkillComponent::IsClimbing() const
{
	return isClimbing;
}

const FPoint2D& UClimbSkillComponent::GetForceJumpOffWall() const
{
	return ForceJumpOffWall;
}
