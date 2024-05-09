// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <PaperZDAnimationComponent.h>
#include <PaperZDAnimInstance.h>
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>
#include <EnhancedInputComponent.h>
#include <InputAction.h>
#include <EnhancedInputSubsystems.h>
#include <NiagaraSystem.h>
#include <NiagaraFunctionLibrary.h>
#include <NiagaraComponent.h>
#include "../../Components/HealthComponent/HealthComponent.h"
#include "../Enemies/MeleeEnemies/Bosses/SkeletonKing/SkeletonKing.h"
#include "../../HUD/Game/HUDGame.h"




AMainPaperCharacter::AMainPaperCharacter() 
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Srping arm"));
	springArmComponent->SetupAttachment(RootComponent);

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComponent->SetupAttachment(springArmComponent);
	
	
	JumpMaxCount = 2;

	m_defoultGravity = 0;
	powerDash = 1000.f;
	timeDash = 0.2f;
	reloadDash = 0.1f;
	isDashing = false;
	canDash = true;

	
}

bool AMainPaperCharacter::GetIsDashing()
{
	return isDashing;
}

int32 AMainPaperCharacter::GetMoney()
{
	return money;
}

void AMainPaperCharacter::SetMoney(int32 newMoney)
{
	if (newMoney < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't set negative value in money"));
		return;
	}
	money = newMoney;
}

void AMainPaperCharacter::AddMoney(int32 addMoney)
{
	if (addMoney < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't add negative value in money"));
		return;
	}
	money += addMoney;
}

void AMainPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	FVector scale = GetActorScale();
	ToNormalize(scale.Normalize());
	
	niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(niagaraSystem, GetRootComponent(), NAME_None, FVector(-20,0,0), FRotator(0), EAttachLocation::Type::KeepRelativeOffset,false,false);
	niagaraComponent->SetFloatParameter("NiagaraTime", timeDash);
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

	enhuncedInput->BindAction(Input.actionDash, ETriggerEvent::Started, this, &AMainPaperCharacter::Dash);
	enhuncedInput->BindAction(Input.actionAttack, ETriggerEvent::Started, this, &AMainPaperCharacter::OnAttack);
}


void AMainPaperCharacter::OnJumped_Implementation()
{
	GetAnimationComponent()->GetAnimInstance()->JumpToNode(Anim.Jump);
}

void AMainPaperCharacter::OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta)
{
	OnJumped_Implementation();
}


void AMainPaperCharacter::RightMove(const FInputActionInstance& instance)
{
	float scale = instance.GetValue().Get<float>();
	
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



void AMainPaperCharacter::Dash()
{
	if (canDash)
	{
		canDash = false;
		isDashing = true;
		
		
		niagaraComponent->Activate(false);

		DisableInput(GetController<APlayerController>());
		GetCharacterMovement()->GravityScale = 0.f;
		GetCharacterMovement()->Velocity = GetActorForwardVector();
	
		LaunchCharacter((GetActorForwardVector() * powerDash * normalizeValues), false, false);

		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMainPaperCharacter::OnStopDash, timeDash, false);
	}
}

void AMainPaperCharacter::OnStopDash()
{
	EnableInput(GetController<APlayerController>());
	GetCharacterMovement()->Velocity = FVector(0.f);
	GetCharacterMovement()->GravityScale = m_defoultGravity;

	isDashing = false;
	FTimerHandle time;
	GetWorld()->GetTimerManager().SetTimer(time, this, &AMainPaperCharacter::OnReloadDash, reloadDash, false);
}

void AMainPaperCharacter::OnReloadDash()
{
	canDash = true;
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
		if (!isDashing)
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

void AMainPaperCharacter::ToNormalize(float normalizeVal)
{
	springArmComponent->TargetArmLength *= normalizeVal;

	GetCharacterMovement()->MaxWalkSpeed *= normalizeVal;
	GetCharacterMovement()->JumpZVelocity *= normalizeVal;
	m_defoultGravity = (GetCharacterMovement()->GravityScale *= normalizeVal);

	this->normalizeValues = normalizeVal;
}
