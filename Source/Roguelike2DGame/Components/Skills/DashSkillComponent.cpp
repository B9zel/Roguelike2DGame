// Fill out your copyright notice in the Description page of Project Settings.


#include "DashSkillComponent.h"
#include "../../Characters/MainCharacter/MainPaperCharacter.h"
#include "../../Data/Structures/SkillStruct.h"

#include <NiagaraComponent.h>
#include <NiagaraFunctionLibrary.h>
#include <GameFramework/CharacterMovementComponent.h>


UDashSkillComponent::UDashSkillComponent()
{
	m_ownerCharacter = nullptr;
	m_DashNiagaraComponent = nullptr;
	niagaraSystem = nullptr;
	
	powerDash = 1000.f;
	timeDash = 0.2f;
	reloadDash = 0.1f;
	isDashing = false;
	canDash = true;
}

void UDashSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	m_ownerCharacter = GetOwner<AMainPaperCharacter>();
	
	m_DashNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(niagaraSystem, m_ownerCharacter->GetRootComponent(), NAME_None, FVector(-20, 0, 0), FRotator(0), EAttachLocation::Type::KeepRelativeOffset, false, false);
	
	if (m_DashNiagaraComponent)
	{
		m_DashNiagaraComponent->SetFloatParameter("NiagaraTime", timeDash);
	}
}


void UDashSkillComponent::Dash()
{
	if (canDash)
	{
		canDash = false;
		isDashing = true;

		m_DashNiagaraComponent->Activate(false);

		FVector forward = m_ownerCharacter->GetActorForwardVector();

		m_ownerCharacter->InputDisable();
		m_ownerCharacter->GetCharacterMovement()->GravityScale = 0.f;
		m_ownerCharacter->GetCharacterMovement()->Velocity = forward;

		m_ownerCharacter->LaunchCharacter((forward * powerDash), false, false);
		m_ownerCharacter->PlayDashAnim();

		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &UDashSkillComponent::OnStopDash, timeDash, false);
	}
}

void UDashSkillComponent::OnStopDash()
{
	m_ownerCharacter->InputEnable();
	m_ownerCharacter->GetCharacterMovement()->Velocity = FVector(0.f);
	m_ownerCharacter->GetCharacterMovement()->GravityScale = m_ownerCharacter->GetDefaultGravity();

	isDashing = false;
	FTimerHandle time;
	GetWorld()->GetTimerManager().SetTimer(time, this, &UDashSkillComponent::OnReloadDash, reloadDash, false);
}

void UDashSkillComponent::OnReloadDash()
{
	canDash = true;
}

void UDashSkillComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	GetOwner<AMainPaperCharacter>()->BindInputDash(this, &UDashSkillComponent::Dash);
}
