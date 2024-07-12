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
class UManaComponent;
class UArtifactUsedDataAsset;
class UBaseWeapon;
class IInteract;
enum class ETypeScroll : uint8;
enum class EWeaponType : uint8;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FImprove, const ETypeScroll&, scroll);


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
	UInputAction* selectSword;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* selectBow;
	

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
	
public:

	virtual void LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride) override;

	void InputEnable();
	void InputDisable();
	float GetDefoultGravity() { return m_defoultGravity; }

	template<class UserClass>
	void BindInputDash(UserClass* object, FSimpleDelegate::TMethodPtr< UserClass > Func);

	UFUNCTION(BlueprintCallable)
	void ImproveStat(const ETypeScroll& typeStat, float mulripier);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UBaseWeapon* GetActiveWeapon() { return activeWeapon; }

	UManaComponent* GetManaComponent() { return manaComponent; }

protected:

	virtual void SetupPlayerInputComponent(UInputComponent* inputComponent) override;
	virtual void BeginPlay() override;
	virtual void OnJumped_Implementation() override;
	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;
	

	virtual void RightMove(const struct FInputActionInstance& instance);

	virtual void OnAttack() override;

	virtual void OnAttackHit() override;

	void StopAttack();

	virtual void OnDeath(AActor* deadActor) override;


	void UseRightArtifact();

	void UseLeftArtifact();
	

	// Change weapon
	void SelectSword();
	void SelectBow();

	void SwitchWeapon(const EWeaponType& type);

public:

	FImprove improveStatDelegate;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UManaComponent* manaComponent;

protected:

	UPROPERTY()
	UBaseWeapon* activeWeapon;

	UPROPERTY(EditAnywhere)
	TMap<EWeaponType, TSubclassOf<UBaseWeapon>> weaponsClass;
	
	UPROPERTY()
	TMap<EWeaponType, UBaseWeapon*> weapons;
	

	UPROPERTY(EditAnywhere)
	FCharacterInputAction Input;
	
	UPROPERTY(EditAnywhere)
	FCharacterAnimation Anim;

private:

	UBaseArtifactComponent** m_rightActiveArtifact;
	UBaseArtifactComponent** m_leftActiveArtifact;

	IInteract* m_rightInteractArtifact;
	IInteract* m_leftInteractArtifact;

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