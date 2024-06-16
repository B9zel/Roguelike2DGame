// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include "../../Components/HealthManaComponent/HealthManaComponent.h"
#include "../Enemies/MeleeEnemies/Bosses/SkeletonKing/SkeletonKing.h"
#include "../../HUD/Game/HUDGame.h"
#include "../../Components/Skills/DashSkillComponent.h"
#include "../../Components/Skills/DoublejumpSkillComponent.h"
#include "../../Components/Artifacts/BaseArtifactComponent.h"
#include "../../Interfaces/InteractInterface.h"

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
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>
#include <NiagaraComponent.h>




AMainPaperCharacter::AMainPaperCharacter() 
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Srping arm"));
	springArmComponent->SetupAttachment(RootComponent);

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComponent->SetupAttachment(springArmComponent);
	
	dashSkillComponent = CreateDefaultSubobject<UDashSkillComponent>(TEXT("Dash"));

	doubleJumpSkillComponent = CreateDefaultSubobject<UDoublejumpSkillComponent>(TEXT("Double jump"));

	m_defoultGravity = 0;
}

void AMainPaperCharacter::BeginPlay()
{
	Super::BeginPlay();


	m_defoultGravity = GetCharacterMovement()->GravityScale;
	UE_LOG(LogTemp, Warning, TEXT("%f"), m_defoultGravity);

	FVector scale = GetActorScale();
	ToNormalize(scale.Normalize());
	
}

void AMainPaperCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}


void AMainPaperCharacter::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	APlayerController* Player = Cast<APlayerController>(GetController());
	if (Player != nullptr)
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

	enhuncedInput->BindAction(Input.useFirstArtifact, ETriggerEvent::Started, this, &AMainPaperCharacter::UseFirstArtifact);
	enhuncedInput->BindAction(Input.useSecondArtifact, ETriggerEvent::Started, this, &AMainPaperCharacter::UseSecondArtifact);
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


UBaseArtifactComponent* AMainPaperCharacter::BindFirstArtifact(TSubclassOf<UBaseArtifactComponent> artifact)
{
	if (firstActiveArtifact != nullptr)
	{
		firstActiveArtifact->DestroyComponent(true);
	}
	if (IsValid(artifact))
	{
		firstActiveArtifact = NewObject<UBaseArtifactComponent>(this, artifact.Get());
		firstActiveArtifact->RegisterComponent();
	}
	else
	{
		firstActiveArtifact = nullptr;
	}

	return firstActiveArtifact;
}

UBaseArtifactComponent* AMainPaperCharacter::BindSecondArtifact(TSubclassOf<UBaseArtifactComponent> artifact)
{
	if (secondActiveArtifact != nullptr)
	{
		secondActiveArtifact->DestroyComponent(true);
	}
	if (IsValid(artifact))
	{
		secondActiveArtifact = NewObject<UBaseArtifactComponent>(this, artifact.Get());
		secondActiveArtifact->RegisterComponent();
	}
	else
	{
		secondActiveArtifact = nullptr;
	}

	return secondActiveArtifact;
}

void AMainPaperCharacter::LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride)
{
	Super::LaunchCharacter(LaunchVelocity, bXYOverride, bZOverride);

	GetAnimationComponent()->GetAnimInstance()->JumpToNode(Anim.Dash);
}


void AMainPaperCharacter::OnAttack()
{
	if (canAttack && !GetCharacterMovement()->IsFalling())
	{
		if (!dashSkillComponent->GetIsDashing())
		{
			canAttack = false;
			isAttacking = true;
			GetAnimationComponent()->GetAnimInstance()->JumpToNode(Anim.Punch);
		}
	}
}

void AMainPaperCharacter::OnAttackHit()
{
	TArray<AActor*> actorsIgnore;
	TArray<FHitResult> res;
	TSubclassOf<UDamageType> damageType;
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * distanceAttack * normalizeValues), capsuleRadiusAttack, capsuleHalfHeightAttack, targetEnums, false, actorsIgnore, EDrawDebugTrace::ForDuration, res, true);


	for (auto& el : res)
	{
		UGameplayStatics::ApplyDamage(el.GetActor(), damage, GetInstigatorController(), this, damageType);
	}
	
	GetWorld()->GetTimerManager().SetTimer(attackReloadTimer, this, &AMainPaperCharacter::OnReloadAttack, timeReloadAttack, false);
}

void AMainPaperCharacter::OnDeath(AActor* deadActor)
{
	Super::OnDeath(deadActor);

	if (deadActor == this)
	{
		GetAnimInstance()->JumpToNode(Anim.Death);
		DisableInput(GetController<APlayerController>());
	}

}

void AMainPaperCharacter::OnSpawn(AActor* spawnActor)
{
	Super::OnSpawn(spawnActor);

	if (spawnActor->StaticClass() == ASkeletonKing::StaticClass())
	{
		GetController<APlayerController>()->GetHUD<AHUDGame>()->EnableEnemyHealthStat(Cast<ABasePaperCharacter>(spawnActor)->GetHealthComponent());
	}
}


void AMainPaperCharacter::UseFirstArtifact()
{
	if (UKismetSystemLibrary::DoesImplementInterface(firstActiveArtifact, UInteract::StaticClass()))
		Cast<IInteract>(firstActiveArtifact)->Interact_Implementation(this);
}

void AMainPaperCharacter::UseSecondArtifact()
{
	if (UKismetSystemLibrary::DoesImplementInterface(secondActiveArtifact, UInteract::StaticClass()))
		Cast<IInteract>(secondActiveArtifact)->Interact_Implementation(this);
}

void AMainPaperCharacter::ToNormalize(float normalizeVal)
{
	springArmComponent->TargetArmLength *= normalizeVal;

	GetCharacterMovement()->MaxWalkSpeed *= normalizeVal;
	GetCharacterMovement()->JumpZVelocity *= normalizeVal;

	this->normalizeValues = normalizeVal;
}

void AMainPaperCharacter::InputEnable()
{
	EnableInput(GetController<APlayerController>());
}


void AMainPaperCharacter::InputDisable()
{
	DisableInput(GetController<APlayerController>());
}
