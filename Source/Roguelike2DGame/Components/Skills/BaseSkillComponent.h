// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKE2DGAME_API UBaseSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UBaseSkillComponent();

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//	void SetSkillDataTable(UDataTable* table) { skillDataTable = table; }
//
//	UDataTable* GetSkillDataTable() { return skillDataTable; }
//
//protected:
//
//	UDataTable* skillDataTable;
		
};
