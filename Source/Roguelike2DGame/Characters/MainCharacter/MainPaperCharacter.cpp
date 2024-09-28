// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPaperCharacter.h"
#include "../../Data/DataAssets/ArtifactUsedDataAsset.h"
#include "../../Data/Enums/EtypeScroll.h"
#include "../../Data/Enums/EWeaponType.h"

#include "../../Controllers/Game/GamePlayerController.h"

#include "../../HUD/Game/HUDGame.h"

#include "../../Components/HealthManaComponent/HealthComponent.h"
#include "../../Components/HealthManaComponent/ManaComponent.h"
#include "../../Components/Skills/DoublejumpSkillComponent.h"
#include "../../Components/Skills/DashSkillComponent.h"
#include "../../Components/Artifacts/BaseArtifactComponent.h"
#include "../../Components/Stat/CharacterStatsComponent.h"

#include "../../Interfaces/Weapon/FinishStageWeapon.h"
#include "../../Interfaces/Weapon/IReloadableWeapon.h"
#include "../../Interfaces/Weapon/MeleeWeapon.h"
#include "../../Interfaces/InteractInterface.h"

#include "Weapon/BaseWeapon.h"

#include "../Enemies/EnemyCharacter.h"

#include <PaperZD/Public/AnimSequences/Players/PaperZDAnimPlayer.h>
//#include <PaperZDAnimationComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/InputComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <EnhancedInputSubsystems.h>
#include <Kismet/GameplayStatics.h>
#include <Camera/CameraComponent.h>



AMainPaperCharacter::AMainPaperCharacter() 
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Srping arm"));
	springArmComponent->SetupAttachment(RootComponent);

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComponent->SetupAttachment(springArmComponent);
	
	manaComponent = CreateDefaultSubobject<UManaComponent>(TEXT("Mana"));

	dashSkillComponent = CreateDefaultSubobject<UDashSkillComponent>(TEXT("Dash"));

	doubleJumpSkillComponent = CreateDefaultSubobject<UDoublejumpSkillComponent>(TEXT("Double jump"));

	m_defoultGravity = 0;
}

void AMainPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_defoultGravity = GetCharacterMovement()->GravityScale;

	UArtifactUsedDataAsset* artifactDataAsset = GetOwner<AGamePlayerController>()->GetArtifactDataAsset();
	m_rightActiveArtifact = &artifactDataAsset->rightArtifact.artifact;
	m_leftActiveArtifact =	&artifactDataAsset->leftArtifact.artifact;

	for (auto& el : weaponsClass)
	{
		AddNewWeapon(el.Key, el.Value);
	}

	check(weaponsObj.Contains(EWeaponType::SWORD));
	activeWeapon = weaponsObj[EWeaponType::SWORD];
}


void AMainPaperCharacter::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	APlayerController* Player = Cast<APlayerController>(GetController());
	if (Player)
	{
		if (auto* inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player->GetLocalPlayer()))
		{
			if (Input.inputMapping)
			{
				inputSystem->AddMappingContext(Input.inputMapping, 0);
			}
			else
			{
				return;
			}
		}
	}
	UEnhancedInputComponent* enhuncedInput = Cast<UEnhancedInputComponent>(inputComponent);
	
	
	enhuncedInput->BindAction(Input.actionRun, ETriggerEvent::Triggered, this, &AMainPaperCharacter::RightMove);

	enhuncedInput->BindAction(Input.actionJump, ETriggerEvent::Started, this, &AMainPaperCharacter::Jump);
	enhuncedInput->BindAction(Input.actionJump, ETriggerEvent::Completed, this, &AMainPaperCharacter::StopJumping);

	enhuncedInput->BindAction(Input.actionAttack, ETriggerEvent::Started, this, &AMainPaperCharacter::OnAttack);
	enhuncedInput->BindAction(Input.actionAttack, ETriggerEvent::Completed, this, &AMainPaperCharacter::StopAttack);

	enhuncedInput->BindAction(Input.useFirstArtifact, ETriggerEvent::Started, this, &AMainPaperCharacter::UseRightArtifact);
	enhuncedInput->BindAction(Input.useSecondArtifact, ETriggerEvent::Started, this, &AMainPaperCharacter::UseLeftArtifact);

	enhuncedInput->BindAction(Input.selectSword, ETriggerEvent::Started, this, &AMainPaperCharacter::SelectSword);
	enhuncedInput->BindAction(Input.selectBow, ETriggerEvent::Started, this, &AMainPaperCharacter::SelectBow);
	enhuncedInput->BindAction(Input.selectScythe, ETriggerEvent::Started, this, &AMainPaperCharacter::SelectScythe);
}


void AMainPaperCharacter::OnJumped_Implementation()
{
	PlayAnimation(Anim.Jump);
}

void AMainPaperCharacter::OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta)
{
	Super::OnWalkingOffLedge_Implementation(PreviousFloorImpactNormal, PreviousFloorImpactNormal, PreviousLocation, TimeDelta);

	OnJumped_Implementation();
}


void AMainPaperCharacter::RightMove(const FInputActionInstance& instance)
{
	float scale = instance.GetValue().Get<float>();
	
	if (GetCharacterMovement()->IsFalling())
	{
		scale *= GetCharacterMovement()->AirControl;
	}
	AddMovementInput(FVector(1,0,0), scale);

	if (scale == 0)
		return;
	
	if (scale < 0)
	{
		GetController()->SetControlRotation(FRotator(0, 180, 0));		
	}
	else
	{
		GetController()->SetControlRotation(FRotator(0, 0, 0));
	}
}

void AMainPaperCharacter::LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	Super::LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);

	PlayAnimation(Anim.Dash);
}

void AMainPaperCharacter::ImproveStat(const ETypeScroll& typeStat, float multiplier)
{
	switch (typeStat)
	{
	case ETypeScroll::MANA:
		manaComponent->SetMaxMana(manaComponent->GetMana() * multiplier);
		break;
	case ETypeScroll::HEALTH:
		healthComponent->SetMaxHP(healthComponent->GetMaxHP() * multiplier);
		break;
	default:
		break;
	}
	improveStatDelegate.Broadcast(typeStat);
}

void AMainPaperCharacter::OnAttack()
{
	if (dashSkillComponent->GetIsDashing())	return;

	activeWeapon->StartAttack();
}

void AMainPaperCharacter::OnAttackHit()
{
	if (UKismetSystemLibrary::DoesImplementInterface(activeWeapon, UMeleeWeapon::StaticClass()))
	{
		Cast<IMeleeWeapon>(activeWeapon)->Attack_Implementation();
		if (UKismetSystemLibrary::DoesImplementInterface(activeWeapon, UReloadableWeapon::StaticClass()))
		{
			Cast<IReloadableWeapon>(activeWeapon)->StartReload_Implementation();
		}
	}
}

void AMainPaperCharacter::StopAttack()
{
	if (!activeWeapon->IsAttacking()) return;
	if (!UKismetSystemLibrary::DoesImplementInterface(activeWeapon, UFinishStageWeapon::StaticClass())) return;
		

	if (UKismetSystemLibrary::DoesImplementInterface(activeWeapon, UReloadableWeapon::StaticClass()))
	{
		Cast<IReloadableWeapon>(activeWeapon)->StartReload_Implementation();
	}
	Cast<IFinishStageWeapon>(activeWeapon)->StopAttack_Implementation();
}

void AMainPaperCharacter::OnDeath_Implementation(AActor* deadActor, AActor* InstigatorActor)
{
	Super::OnDeath_Implementation(deadActor, InstigatorActor);

	if (deadActor == this)
	{
		PlayAnimation(Anim.Death);
		InputDisable();
	}
	else if (InstigatorActor == this)
	{
		GetActiveWeapon()->AddSouls(Cast<AEnemyCharacter>(deadActor)->GetSoulsDrop());
	}
}


void AMainPaperCharacter::UseRightArtifact()
{
	if (UKismetSystemLibrary::DoesImplementInterface(*m_rightActiveArtifact, UInteract::StaticClass()))
	{
		if (!m_rightInteractArtifact)
		{
			m_rightInteractArtifact = Cast<IInteract>(*m_rightActiveArtifact);
		}
		m_rightInteractArtifact->Interact_Implementation(this);
	}
}

void AMainPaperCharacter::UseLeftArtifact()
{
	if (UKismetSystemLibrary::DoesImplementInterface(*m_leftActiveArtifact, UInteract::StaticClass()))
	{
		if (!m_leftInteractArtifact)
		{
			m_leftInteractArtifact = Cast<IInteract>(*m_leftActiveArtifact);
		}
		m_leftInteractArtifact->Interact_Implementation(this);
	}
}

void AMainPaperCharacter::SwitchWeapon(const EWeaponType& type)
{
	if (type != activeWeapon->GetWeaponType())
	{
		if (weaponsObj.Contains(type))
		{
			activeWeapon = weaponsObj[type];
		}
	}
}

void AMainPaperCharacter::AddNewWeapon(const EWeaponType& typeWeapon, TSubclassOf<class UBaseWeapon> newWeapon)
{
	if (!weaponsObj.Contains(typeWeapon))
	{
		weaponsObj.Add(typeWeapon, NewObject<UBaseWeapon>(this, newWeapon.Get()));
	}
}

void AMainPaperCharacter::SelectSword()
{
	SwitchWeapon(EWeaponType::SWORD);
}

void AMainPaperCharacter::SelectBow()
{
	SwitchWeapon(EWeaponType::BOW);
}

void AMainPaperCharacter::SelectScythe()
{
	SwitchWeapon(EWeaponType::SCYTHE);
}

void AMainPaperCharacter::InputEnable()
{
	EnableInput(GetController<APlayerController>());
}

void AMainPaperCharacter::InputDisable()
{
	DisableInput(GetController<APlayerController>());
}

void AMainPaperCharacter::OnEndAnimAttack()
{
	GetActiveWeapon()->OnEndAnimationAttack();
}