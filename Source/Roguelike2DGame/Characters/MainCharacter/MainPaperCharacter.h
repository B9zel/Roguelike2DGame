// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <EnhancedInputComponent.h>
#include <InputAction.h>

#include "../BasePaperCharacter.h"
#include "MainPaperCharacter.generated.h"


class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UDashSkillComponent;
class UDoublejumpSkillComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UBaseArtifactComponent;


USTRUCT(BlueprintType)
struct FCharacterInputAction
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* actionRun;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* actionJump;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* actionDash;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* actionAttack;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* useFirstArtifact;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* useSecondArtifact;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* interact;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* inputMapping;
};


USTRUCT(BlueprintType)
struct FCharacterAnimation
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, Category = "Anim")
	FName Jump;

	UPROPERTY(EditAnywhere, Category = "Anim")
	FName Punch;

	UPROPERTY(EditAnywhere, Category = "Anim")
	FName Dash;

	UPROPERTY(EditAnywhere, Category = "Anim")
	FName Death;
};


UCLASS()
class ROGUELIKE2DGAME_API AMainPaperCharacter : public ABasePaperCharacter
{
	GENERATED_BODY()

public:

	AMainPaperCharacter();
	
	void InputEnable();

	void InputDisable();

	float GetDefoultGravity() { return m_defoultGravity; }

	template<class UserClass>
	void BindInputDash(UserClass* object, FSimpleDelegate::TMethodPtr< UserClass > Func);

	UFUNCTION(BlueprintCallable)
	UBaseArtifactComponent* BindFirstArtifact(TSubclassOf<UBaseArtifactComponent> artifact);
	UFUNCTION(BlueprintCallable)
	UBaseArtifactComponent* BindSecondArtifact(TSubclassOf<UBaseArtifactComponent> artifact);

	virtual void LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride) override;

protected:

	virtual void SetupPlayerInputComponent(UInputComponent* inputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float deltaTime) override;
	
	
	virtual void OnJumped_Implementation() override;

	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;
	
	virtual void RightMove(const struct FInputActionInstance& instance);


	virtual void OnAttack() override;

	virtual void OnAttackHit() override;

	virtual void OnDeath(AActor* deadActor) override;

	virtual void OnSpawn(AActor* spawnActor) override;



	virtual void UseFirstArtifact();

	virtual void UseSecondArtifact();
	
	void ToNormalize(float normalizeVal);

protected:

	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USpringArmComponent* springArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* cameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDashSkillComponent* dashSkillComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDoublejumpSkillComponent* doubleJumpSkillComponent;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* niagaraSystem;
	

protected:
	
	// Game values
	UPROPERTY(EditAnywhere)
	FCharacterInputAction Input;
	
	UPROPERTY(EditAnywhere)
	FCharacterAnimation Anim;
	
	
	UPROPERTY(EditAnywhere)
	float capsuleRadiusAttack;

	UPROPERTY(EditAnywhere)
	float capsuleHalfHeightAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float normalizeValues;

	UBaseArtifactComponent* firstActiveArtifact;

	UBaseArtifactComponent* secondActiveArtifact;

private:

	float m_defoultGravity;
};

template<class UserClass>
inline void AMainPaperCharacter::BindInputDash(UserClass* object, FSimpleDelegate::TMethodPtr<UserClass> Func)
{
	if (UEnhancedInputComponent* enhuncedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		enhuncedInput->BindAction(Input.actionDash, ETriggerEvent::Started, object, Func);
	}
}
