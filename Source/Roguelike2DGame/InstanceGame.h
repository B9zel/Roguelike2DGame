// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "InstanceGame.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API UInstanceGame : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void AddArtifactClass(TSubclassOf<class UBaseArtifactComponent>& artifact);

	UFUNCTION(BlueprintCallable)
	void AddSkillClass(TSubclassOf<class UBaseSkillComponent>& skill);


	UFUNCTION(BlueprintCallable, BLueprintPure)
	const TArray<TSubclassOf<class UBaseArtifactComponent>>& GetOpenArtifacts() { return m_openArtifactsClass; }

	UFUNCTION(BlueprintCallable, BLueprintPure)
	const TArray<TSubclassOf<class UBaseSkillComponent>>& GetOpenSkills() { return m_openSkillsClass; }

protected:

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UBaseArtifactComponent>> m_openArtifactsClass;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UBaseSkillComponent>> m_openSkillsClass;
};
