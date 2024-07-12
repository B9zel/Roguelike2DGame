// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_HeathPoints.generated.h"


class UProgressBar;
class UTextBlock;
class UHealthComponent;
class AMainPaperCharacter;


UCLASS()
class ROGUELIKE2DGAME_API UW_HeathPoints : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_HealthPoints;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_MaxHP;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_CurrentHP;

	UPROPERTY()
	UHealthComponent* healthComponentOfCharacter;

	AMainPaperCharacter* ownerCharacter;

protected:

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void UpdateHealth(AActor* instigatorDamage);

	UFUNCTION()
	void ImproveOwnerCharacter(const ETypeScroll& typeImprove);

	UFUNCTION()
	void PostInit(AActor* actor);
};
