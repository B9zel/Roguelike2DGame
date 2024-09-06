// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceLoader.h"
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/AssetManager.h>
#include <Async/AsyncWork.h>



TUniquePtr<ResourceLoader> ResourceLoader::m_Instance = nullptr;


ResourceLoader* ResourceLoader::Create()
{
	if (!m_Instance.IsValid())
	{
		ResourceLoader* buffer = new ResourceLoader();
		if (buffer)
		{
			m_Instance.Reset(buffer);
		}
		else
		{
			UE_LOG(LogResourceLoad, Display, TEXT("Can't create \"ResourceLoader\""))
			return nullptr;
		}
	}

	return m_Instance.Get();
}

LoaderHandle& ResourceLoader::ResourceAsyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream, FStreamableDelegate DelegateToCall)
{
	if (TargetToStream.IsNull())
	{
		UE_LOG(LogResourceLoad, Display, TEXT("SoftObjectPath is null"));
		return handle;
	}

	const TUniquePtr<ResourceLoader>& instance = ResourceLoader::GetLoaderInstance();
	FScopeLock lock(&instance->m_Mutex);

	if (UAssetManager::IsInitialized())
	{
		TSharedPtr<FStreamableHandle> loadResource = UAssetManager::GetStreamableManager().RequestAsyncLoad(TargetToStream, FStreamableDelegate::CreateRaw(instance.Get(), &ResourceLoader::OnLoader));
		instance->streamableLoading.Add(loadResource, &handle);
	}

	return handle;
}

LoaderHandle& ResourceLoader::ResourceSyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream)
{
	if (TargetToStream.IsNull())
	{
		UE_LOG(LogResourceLoad, Display, TEXT("SoftObjectPath is null"));
		return handle;
	}

	if (UAssetManager::IsInitialized())
	{
		const TUniquePtr<ResourceLoader>& instance = ResourceLoader::GetLoaderInstance();

		TSharedPtr<FStreamableHandle> loadResource = UAssetManager::GetStreamableManager().RequestSyncLoad(TargetToStream);

		if (loadResource->HasLoadCompleted())
		{
			uint64 newID = instance->GetID();
			instance->streamableHandler.Add(newID, loadResource);
			handle.id = newID;
		}
	}
	return handle;
}

UObject* ResourceLoader::GetData(const LoaderHandle handler)
{
	if (!m_Instance) return nullptr;

	if (handler.IsValid())
	{
		return ResourceLoader::GetLoaderInstance()->streamableHandler.Find(handler.id)->Get()->GetLoadedAsset();
	}

	return nullptr;
}

void ResourceLoader::ClearData()
{
	if (!streamableHandler.IsEmpty())
	{
		streamableHandler.Empty();
	}
	if (!streamableLoading.IsEmpty())
	{
		streamableLoading.Empty();
	}
}

void ResourceLoader::OnLoader()
{	
	FScopeLock lock(&m_Mutex);

	TArray<TSharedPtr<FStreamableHandle>> deleteElements;
	for (auto& handler : streamableLoading)
	{
		if (handler.Key->HasLoadCompleted())
		{
			uint64 newID = GetID();

			handler.Value->id = newID;
			streamableHandler.Add(newID, handler.Key);

			OnLoadDelegate.Broadcast(handler.Key->GetLoadedAsset());
			deleteElements.Add(handler.Key);
		}
	}

	for (auto& handler : deleteElements)
	{
		streamableLoading.Remove(handler);
	}
}


void ResourceLoader::DestroyLoader()
{
	ClearData();
	m_Instance.Reset();
}

uint64 ResourceLoader::GetID()
{
	return ++IDCounter;
}

const TUniquePtr<ResourceLoader>& ResourceLoader::GetLoaderInstance()
{
	return m_Instance;
}