// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Data/ResourceLoader.h"
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

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TArray<TSoftClassPtr<class UBaseArtifactComponent>>& GetOpenArtifacts() { return openArtifactsClass; }

	ResourceLoader* GetResourceLoader();

protected:

	virtual void Init() override;
	virtual void Shutdown() override;
	
protected:

	UPROPERTY(EditAnywhere)
	TArray<TSoftClassPtr<class UBaseArtifactComponent>> openArtifactsClass;

private:

	//UPROPERTY()
	class ResourceLoader* m_ResourceLoader;
};
