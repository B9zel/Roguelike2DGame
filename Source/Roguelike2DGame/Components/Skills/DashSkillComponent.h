// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSkillComponent.h"
#include "DashSkillComponent.generated.h"


class UNiagaraSystem;


UCLASS()
class ROGUELIKE2DGAME_API UDashSkillComponent : public UBaseSkillComponent
{
	GENERATED_BODY()

public:

	UDashSkillComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsDashing() { return isDashing; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetCanDash() { return canDash; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetTimeDash() { return timeDash; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetPowerDash() { return powerDash; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetTimeReloadDash() { return reloadDash; }

	virtual void Dash();

	virtual void Activate(bool bReset = false) override;

protected:

	virtual void BeginPlay() override;

	virtual void OnStopDash();

	virtual void OnReloadDash();


protected:

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* niagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float timeDash;

	UPROPERTY(EditAnywhere)
	float powerDash;

	UPROPERTY(EditAnywhere)
	float reloadDash;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isDashing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool canDash;

private:

	class AMainPaperCharacter* m_ownerCharacter;

	class UNiagaraComponent* m_DashNiagaraComponent;

};