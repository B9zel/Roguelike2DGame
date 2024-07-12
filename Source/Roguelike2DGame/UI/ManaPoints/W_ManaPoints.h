// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ManaPoints.generated.h"



class UProgressBar;
class UTextBlock;
class UManaComponent;


UCLASS()
class ROGUELIKE2DGAME_API UW_ManaPoints : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void PostInit(AActor* actorSpawn);

protected:

	// Bind property
	UPROPERTY(meta=(BindWidget))
	UProgressBar* PB_ManaPoints;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TB_MaxMana;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TB_CurrentMana;
	// 

	UManaComponent* manaComponentOfCharacter;

};
