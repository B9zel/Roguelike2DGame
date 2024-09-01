// Fill out your copyright notice in the Description page of Project Settings.

#include "InstanceGame.h"
#include "Components/Artifacts/BaseArtifactComponent.h"
#include "Components/Skills/BaseSkillComponent.h"





void UInstanceGame::AddArtifactClass(TSoftClassPtr<class UBaseArtifactComponent> artifact)
{	
#if UE_BUILD_DEBUG || WITH_EDITOR
	if (openArtifactsClass.Contains(artifact))
	{
		UE_LOG(LogTemp, Warning, TEXT("There is already an artifact in the array %s"), *artifact.Get()->GetName());
		return;
	}
#endif // 
	
	openArtifactsClass.Add(artifact);
}

ResourceLoader* UInstanceGame::GetResourceLoader()
{
	return m_ResourceLoader;
}

void UInstanceGame::Init()
{
	m_ResourceLoader = (ResourceLoader::Create());
	//m_ResourceLoader->ClearData();
}

void UInstanceGame::Shutdown()
{
	Super::Shutdown();

	m_ResourceLoader->DestroyLoader();
	m_ResourceLoader = nullptr;
}
