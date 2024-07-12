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
#include "../../Components/Artifacts/BaseArtifactComponent.h"
#include "../../Components/Stat/CharacterStatsComponent.h"
#include "../../Components/Skills/DashSkillComponent.h"

#include "../../Interfaces/Weapon/MeleeWeapon.h"
#include "../../Interfaces/InteractInterface.h"
#include "../../Interfaces/Weapon/DistanceWeapon.h"
//#include "Weapon/DistanceWeapon/BaseDistanceWeapon.h"
//#include "Weapon/MeleeWeapon/BaseMeleeWeapon.h"
#include "Weapon/BaseWeapon.h"


#include <GameFramework/SpringArmComponent.h>
#include <PaperZDAnimationComponent.h>
#include <PaperZDAnimInstance.h>
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>
#include <EnhancedInputSubsystems.h>





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
	m_leftActiveArtifact = &artifactDataAsset->leftArtifact.artifact;

	for (auto& el : weaponsClass)
	{
		weapons.Add(el.Key, NewObject<UBaseWeapon>(this, el.Value.Get()));
	}
	activeWeapon = weapons[EWeaponType::SWORD];
}


void AMainPaperCharacter::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	APlayerController* Player = Cast<APlayerController>(GetController());
	if (Player)
	{
		if (class UEnhancedInputLocalPlayerSubsystem* inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player->GetLocalPlayer()))
		{
			if (Input.inputMapping != nullptr)
			{
				inputSystem->AddMappingContext(Input.inputMapping, 0);
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
}


void AMainPaperCharacter::OnJumped_Implementation()
{
	GetAnimationComponent()->GetAnimInstance()->JumpToNode(Anim.Jump);
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

	GetAnimationComponent()->GetAnimInstance()->JumpToNode(Anim.Dash);
}

void AMainPaperCharacter::ImproveStat(const ETypeScroll& typeStat, float multiplier)
{
	switch (typeStat)
	{
	case ETypeScroll::MANA:
		manaComponent->SetMaxMana(manaComponent->GetMana() * multiplier);
		break;
	case ETypeScroll::AGILITY:
		statsComponent->SetTimeReloadAttack(statsComponent->GetTimeReloadAttack() * multiplier);
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
	if (activeWeapon->GetCanAttack() && !GetCharacterMovement()->IsFalling())
	{
		if (dashSkillComponent->GetIsDashing())
		{
			return;
		}

		activeWeapon->SetCanAttack(false);
		activeWeapon->SetIsAttacking(true);


		if (UKismetSystemLibrary::DoesImplementInterface(activeWeapon, UDistanceWeapon::StaticClass()))
		{
			Cast<IDistanceWeapon>(activeWeapon)->StartAttack_Implementation();
		}
		else if (UKismetSystemLibrary::DoesImplementInterface(activeWeapon, UMeleeWeapon::StaticClass()))
		{
			GetAnimInstance()->JumpToNode(Anim.Punch);
		}
	}
}

void AMainPaperCharacter::OnAttackHit()
{
	if (UKismetSystemLibrary::DoesImplementInterface(activeWeapon, UMeleeWeapon::StaticClass()))
	{
		static IMeleeWeapon* meleeWeapon;
		if (!meleeWeapon)
		{
			meleeWeapon = Cast<IMeleeWeapon>(activeWeapon);
		}
		activeWeapon->StartReload();
		meleeWeapon->Attack_Implementation();
	}
	//GetWorld()->GetTimerManager().SetTimer(attackReloadTimer, this, &AMainPaperCharacter::OnReloadAttack, statsComponent->GetTimeReloadAttack(), false);
}

void AMainPaperCharacter::StopAttack()
{
	if (UKismetSystemLibrary::DoesImplementInterface(activeWeapon, UDistanceWeapon::StaticClass()))
	{
		static IDistanceWeapon* distanWeapon;
		if (!distanWeapon)
		{
			distanWeapon = Cast<IDistanceWeapon>(activeWeapon);
		}
		activeWeapon->StartReload();
		distanWeapon->StopAttack_Implementation();
	}
}


void AMainPaperCharacter::OnDeath(AActor* deadActor)
{
	Super::OnDeath(deadActor);

	if (deadActor == this)
	{
		GetAnimInstance()->JumpToNode(Anim.Death);
		InputDisable();
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

void AMainPaperCharacter::SelectSword()
{
	SwitchWeapon(EWeaponType::SWORD);
}

void AMainPaperCharacter::SelectBow()
{
	SwitchWeapon(EWeaponType::BOW);
}

void AMainPaperCharacter::SwitchWeapon(const EWeaponType& type)
{
	if (type != activeWeapon->GetWeaponType())
	{
		if (weapons.Contains(type))
		{
			activeWeapon = weapons[type];
		}
	}
}

void AMainPaperCharacter::InputEnable()
{
	EnableInput(GetController<APlayerController>());
}


void AMainPaperCharacter::InputDisable()
{
	DisableInput(GetController<APlayerController>());
}
