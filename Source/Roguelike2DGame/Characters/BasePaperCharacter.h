// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BasePaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API ABasePaperCharacter : public APaperZDCharacter
{
	GENERATED_BODY()
	
public:

	ABasePaperCharacter();

protected:

	UPROPERTY(EditAnywhere)
	class UHealthComponent* healthComponent;

};
