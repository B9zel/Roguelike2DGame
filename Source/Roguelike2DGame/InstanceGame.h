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
	void AddArtifactClass(TSoftClassPtr<class UBaseArtifactComponent> artifact);

	//UFUNCTION(BlueprintCallable)
	//void AddSkillClass(TSoftClassPtr<class UBaseSkillComponent>& skill);


	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TArray<TSoftClassPtr<class UBaseArtifactComponent>>& GetOpenArtifacts() { return openArtifactsClass; }

	//UFUNCTION(BlueprintCallable, BLueprintPure)
	//const TArray<TSubclassOf<class UBaseSkillComponent>>& GetOpenSkills() { return m_openSkillsClass; }

protected:

	UPROPERTY(EditAnywhere)
	TArray<TSoftClassPtr<class UBaseArtifactComponent>> openArtifactsClass;
	//UPROPERTY(EditAnywhere)
	//TArray<TSoftClassPtr<class UBaseSkillComponent>> m_openSkillsClass;
	
};
