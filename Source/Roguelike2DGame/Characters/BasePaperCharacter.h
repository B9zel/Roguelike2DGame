
#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BasePaperCharacter.generated.h"


class UCharacterStatsComponent;
class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseCharacterDelegateWithoutParam);



UCLASS(Abstract)
class ROGUELIKE2DGAME_API ABasePaperCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

	ABasePaperCharacter();

public:	

	UFUNCTION(BlueprintCallable)
	virtual void OnAttack() PURE_VIRTUAL(ABasePaperCharacter::OnAttack,);

	//Getters
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UHealthComponent* GetHealthComponent() { return healthComponent; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCharacterStatsComponent* GetStatsComponent() { return statsComponent; }

protected:

	virtual void BeginPlay() override;

	// Call in animation blueprint, when weapon hit with enemy
	UFUNCTION(BlueprintCallable)
	virtual void OnAttackHit() PURE_VIRTUAL(ABasePaperCharacter::OnAttackHit, );

	UFUNCTION()
	virtual void OnDeath(AActor* deadActor, AActor* instigatorActor) {}
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

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCharacterStatsComponent* statsComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* healthComponent;

	FTimerHandle attackReloadTimer;
};