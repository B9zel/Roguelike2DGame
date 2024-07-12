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

//void UInstanceGame::AddSkillClass(TSubclassOf<class UBaseSkillComponent>& skill)
//{
//	
//#if UE_BUILD_DEBUG || WITH_EDITOR
//	if (m_openSkillsClass.Contains(skill))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("There is already an skill in the array %s"), skill);
//		return;
//	}
//#endif // 
//	m_openSkillsClass.Add(skill);
//}
