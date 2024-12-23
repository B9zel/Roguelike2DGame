
#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BasePaperCharacter.generated.h"


class UCharacterStatsComponent;
class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseCharacterDelegateWithoutParam);


/*
	Base class for all characters
*/
UCLASS(Abstract)
class ROGUELIKE2DGAME_API ABasePaperCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	ABasePaperCharacter();

public:

	UFUNCTION(BlueprintCallable)
	virtual void OnAttack() PURE_VIRTUAL(ABasePaperCharacter::OnAttack, );

	UFUNCTION(BlueprintCallable)
	void PlayAnimation(FName nameAnim);

	//Getters
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UHealthComponent* GetHealthComponent() { return healthComponent; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCharacterStatsComponent* GetStatsComponent() { return statsComponent; }


	void EnableCharacterMovement();
	void DisableCharacterMovement();

	void ResetMove();

protected:

	virtual void BeginPlay() override;
	virtual void OnDeath_Implementation(AActor* deadActor, AActor* instigatorActor) {}

	// Call in animation blueprint, when weapon hit with enemy
	UFUNCTION(BlueprintCallable)
	virtual void OnAttackHit();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeath(AActor* deadActor, AActor* instigatorActor);


	UFUNCTION()
	virtual void OnSpawn(AActor* deadActor) {}
	UFUNCTION(BlueprintCallable)
	virtual void OnReloadAttack();
	UFUNCTION(BlueprintCallable)
	virtual void OnEndAnimAttack();

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FBaseCharacterDelegateWithoutParam endAnimAttack;
	UPROPERTY(BlueprintAssignable)
	FBaseCharacterDelegateWithoutParam reloadAttack;
	UPROPERTY(BlueprintAssignable)
	FBaseCharacterDelegateWithoutParam hitAttack;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCharacterStatsComponent* statsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* healthComponent;

	FTimerHandle attackReloadTimer;


private:

	TEnumAsByte<EMovementMode> m_bufferMovementMode;
};