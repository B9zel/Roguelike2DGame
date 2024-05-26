// Fill out your copyright notice in the Description page of Project Settings.


#include "DoublejumpSkillComponent.h"
#include <GameFramework/Character.h>

void UDoublejumpSkillComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	if (ACharacter* owner = GetOwner<ACharacter>())
	{
		owner->JumpMaxCount = 2;
	}
}
