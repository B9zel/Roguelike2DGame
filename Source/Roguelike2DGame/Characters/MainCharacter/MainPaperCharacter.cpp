// Fill out your copyright notice in the Description page of Project Settings.
#include "MainPaperCharacter.h"

#include "../../Data/DataAssets/ArtifactUsedDataAsset.h"
#include "../../Data/Enums/EtypeScroll.h"
#include "../../Data/Enums/EWeaponType.h"

#include "../../Controllers/Game/GamePlayerController.h"

#include "../../HUD/Game/HUDGame.h"

#include "../../Components/Artifacts/BaseArtifactComponent.h"
#include "../../Components/HealthManaComponent/HealthComponent.h"
#include "../../Components/HealthManaComponent/ManaComponent.h"
#include "../../Components/Skills/DashSkillComponent.h"
#include "../../Components/Skills/DoublejumpSkillComponent.h"
#include "../../Components/Skills/ClimbSkillComponent.h"
#include "../../Components/Stat/CharacterStatsComponent.h"

#include "../../Interfaces/InteractInterface.h"
#include "../../Interfaces/Weapon/FinishStageWeapon.h"
#include "../../Interfaces/Weapon/IReloadableWeapon.h"
#include "../../Interfaces/Weapon/MeleeWeapon.h"

#include "Weapon/BaseWeapon.h"

#include "../Enemies/EnemyCharacter.h"

#include <PaperZD/Public/AnimSequences/Players/PaperZDAnimPlayer.h>
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

	climbComponent = CreateDefaultSubobject<UClimbSkillComponent>(TEXT("Climb"));

	m_defaultGravity = 0;
	m_isCurrentMove = false;
}

void AMainPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_defaultGravity = GetCharacterMovement()->GravityScale;

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
	UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(inputComponent);
	
	
	enhancedInput->BindAction(Input.actionRun, ETriggerEvent::Triggered, this, &AMainPaperCharacter::RightMove);

	enhancedInput->BindAction(Input.actionJump, ETriggerEvent::Started, this, &AMainPaperCharacter::Jump);
	enhancedInput->BindAction(Input.actionJump, ETriggerEvent::Completed, this, &AMainPaperCharacter::StopJumping);

	enhancedInput->BindAction(Input.actionAttack, ETriggerEvent::Started, this, &AMainPaperCharacter::OnAttack);
	enhancedInput->BindAction(Input.actionAttack, ETriggerEvent::Completed, this, &AMainPaperCharacter::StopAttack);

	enhancedInput->BindAction(Input.useFirstArtifact, ETriggerEvent::Started, this, &AMainPaperCharacter::UseRightArtifact);
	enhancedInput->BindAction(Input.useSecondArtifact, ETriggerEvent::Started, this, &AMainPaperCharacter::UseLeftArtifact);

	enhancedInput->BindAction(Input.selectSword, ETriggerEvent::Started, this, &AMainPaperCharacter::SelectSword);
	enhancedInput->BindAction(Input.selectBow, ETriggerEvent::Started, this, &AMainPaperCharacter::SelectBow);
	enhancedInput->BindAction(Input.selectScythe, ETriggerEvent::Started, this, &AMainPaperCharacter::SelectScythe);
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
	{
		m_isCurrentMove = false;
		return;
	}
	
	m_isCurrentMove = true;
	if (scale < 0)
	{
		GetController()->SetControlRotation(FRotator(0, 180, 0));		
	}
	else
	{
		GetController()->SetControlRotation(FRotator(0, 0, 0));
	}
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
		DisableCharacterMovement();
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

void AMainPaperCharacter::PlayDashAnim()
{
	PlayAnimation(Anim.Dash);
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

void AMainPaperCharacter::Jump()
{
	if (!climbComponent->IsActive())
	{
		Super::Jump();
		return;
	}

	if (!climbComponent->IsClimbing())
	{
		Super::Jump();
		return;
	}
	FPoint2D force = climbComponent->GetForceJumpOffWall();
	GetController()->SetControlRotation(FRotator(0.0, GetActorRotation().Yaw + 180, 0.0));
	LaunchCharacter(FVector((-GetActorForwardVector() * force.X).X, 0.0f, force.Z), true, true);
}
