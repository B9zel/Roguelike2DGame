
#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BasePaperCharacter.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseCharacterDelegateWithoutParam);


class UCharacterStatsComponent;
class UHealthComponent;


UCLASS(Abstract)
class ROGUELIKE2DGAME_API ABasePaperCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

	ABasePaperCharacter();

public:	

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UHealthComponent* GetHealthComponent() { return healthComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCharacterStatsComponent* GetStatsComponent() { return statsComponent; }

	UFUNCTION(BlueprintCallable)
	TArray<TEnumAsByte<EObjectTypeQuery>>& GetTargetEnumsObject() { return targetEnums; }

	UFUNCTION(BlueprintCallable)
	virtual void OnAttack() PURE_VIRTUAL(ABasePaperCharacter::OnAttack,);

protected:

	virtual void BeginPlay() override;

	// Call in animation blueprint, when weapon hit with enemy
	UFUNCTION(BlueprintCallable)
	virtual void OnAttackHit() PURE_VIRTUAL(ABasePaperCharacter::OnAttackHit, );

	UFUNCTION()
	virtual void OnTakePlayerDamage(AActor* instigatorDamage) {};

	UFUNCTION()
	virtual void OnDeath(AActor* deadActor) {}

	UFUNCTION()
	virtual void OnSpawn(AActor* deadActor) {}

	UFUNCTION(BlueprintCallable)
	virtual void OnReloadAttack();

	UFUNCTION(BlueprintCallable)
	virtual void OnEndAnimAttack();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCharacterStatsComponent* statsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* healthComponent;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> targetEnums;


	FTimerHandle attackReloadTimer;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FBaseCharacterDelegateWithoutParam endAnimAttack;

	UPROPERTY(BlueprintAssignable)
	FBaseCharacterDelegateWithoutParam reloadAttack;
};