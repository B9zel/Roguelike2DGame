// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceLoader.h"
#include <Engine/AssetManager.h>


uint64 ResourceLoader::IDCounter = 0;


const TUniquePtr<ResourceLoader>& ResourceLoader::Create()
{
	if (!m_Instance.IsValid())
	{
		m_Instance = MakeUnique<ResourceLoader>();
	}
	return m_Instance;
}

LoaderHandle& ResourceLoader::ResourceAsyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream, FStreamableDelegate DelegateToCall)
{
	if (UAssetManager::IsInitialized())
	{
		const TUniquePtr<ResourceLoader>& instance = ResourceLoader::GetLoaderInstance();
		const uint64 newID = instance->GetID();
		const int32 index = instance->streamableloading.Emplace(UAssetManager::GetStreamableManager().RequestAsyncLoad(TargetToStream, FStreamableDelegate::CreateUObject(instance.Get(), &ResourceLoader::OnLoader)));
		
		instance->streamableHandler[newID] = instance->streamableloading[index];
		handle.id = newID;
	}

	return handle;
}

const TUniquePtr<ResourceLoader>& ResourceLoader::GetLoaderInstance()
{
	return m_Instance;
}

const TSharedPtr<FStreamableHandle>& ResourceLoader::GetData(const LoaderHandle& handler)
{
	if (handler.IsValid())
	{
		return streamableHandler[handler.id];
	}
	return nullptr;
}

void ResourceLoader::OnLoader()
{	
	TArray<TSharedPtr<FStreamableHandle>> deleteElements;
	for (auto& handler : streamableloading)
	{
		if (handler->HasLoadCompleted())
		{
			//OnLoaderDelegate.Bloadcast(handler->GetLoadedAsset());
			deleteElements.Emplace(handler);
		}
	}

	for (auto& handler : deleteElements)
	{
		streamableloading.Remove(handler);
	}
	deleteElements.Empty();
}

uint64 ResourceLoader::GetID()
{
	return ++IDCounter;
}
