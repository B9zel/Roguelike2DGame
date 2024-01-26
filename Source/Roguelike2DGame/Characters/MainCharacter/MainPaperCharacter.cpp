// Fill out your copyright notice in the Description page of Project Settings.

#define DEFAULT_GRAVITY_SCALE 1.f

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







AMainPaperCharacter::AMainPaperCharacter()
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Srping arm"));
	springArmComponent->SetupAttachment(RootComponent);

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComponent->SetupAttachment(springArmComponent);

	GetCharacterMovement()->GravityScale = DEFAULT_GRAVITY_SCALE;
	
	JumpMaxCount = 2;

	powerDash = 1000.f;
	timeDash = 0.2f;
	reloadDash = 0.1f;
	isDashing = false;
	canDash = true;

}

void AMainPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}


void AMainPaperCharacter::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	APlayerController* Player = Cast<APlayerController>(GetController());
	if (Player != nullptr)
	{
		if (class UEnhancedInputLocalPlayerSubsystem* inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player->GetLocalPlayer()))
		{
			if (inputMapping != nullptr)
			{
				inputSystem->AddMappingContext(inputMapping, 0);
			}
		}
	}
	

	UEnhancedInputComponent* enhuncedInput = Cast<UEnhancedInputComponent>(inputComponent);
	
	enhuncedInput->BindAction(actionRun, ETriggerEvent::Triggered, this, &AMainPaperCharacter::RightMove);

	enhuncedInput->BindAction(actionJump, ETriggerEvent::Started, this, &AMainPaperCharacter::Jump);
	enhuncedInput->BindAction(actionJump, ETriggerEvent::Completed, this, &AMainPaperCharacter::StopJumping);

	enhuncedInput->BindAction(actionDash, ETriggerEvent::Started, this, &AMainPaperCharacter::Dash);
	enhuncedInput->BindAction(actionAttack, ETriggerEvent::Started, this, &AMainPaperCharacter::OnAttack);
}


void AMainPaperCharacter::OnJumped_Implementation()
{
	GetAnimationComponent()->GetAnimInstance()->JumpToNode("Jump");
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

		
		DisableInput(GetController<APlayerController>());
		GetCharacterMovement()->GravityScale = 0.f;
		GetCharacterMovement()->Velocity = GetActorForwardVector();
	
		LaunchCharacter((GetActorForwardVector() * powerDash), false, false);

		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMainPaperCharacter::OnStopDash, timeDash, false);
	}
}

void AMainPaperCharacter::OnStopDash()
{
	EnableInput(GetController<APlayerController>());
	GetCharacterMovement()->Velocity = FVector(0.f);
	GetCharacterMovement()->GravityScale = DEFAULT_GRAVITY_SCALE;

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

	GetAnimationComponent()->GetAnimInstance()->JumpToNode("Dash");
}




void AMainPaperCharacter::OnAttack()
{
	if (canAttack)
	{
		canAttack = false;
		isAttacking = true;
		GetAnimationComponent()->GetAnimInstance()->JumpToNode("Punch");
	}
}

void AMainPaperCharacter::OnAttackHit()
{
	TArray<AActor*> actorsIgnore;
	TArray<FHitResult> res;
	TSubclassOf<UDamageType> damageType;
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * distanceAttack), 15, 35, targetEnums, false, actorsIgnore, EDrawDebugTrace::ForDuration, res, true);


	for (auto& el : res)
	{
		UGameplayStatics::ApplyDamage(el.GetActor(), damage, GetInstigatorController(), this, damageType);
	}
	
	GetWorld()->GetTimerManager().SetTimer(attackReloadTimer, this, &AMainPaperCharacter::OnReloadAttack, timeReloadAttack, false);
}
