// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceLoader.h"
#include <Engine/AssetManager.h>
#include <Runtime/Engine/Classes/Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include <Async/AsyncWork.h>


uint64 UResourceLoader::IDCounter = 0;
TUniquePtr<UResourceLoader> UResourceLoader::m_Instance = nullptr;


UResourceLoader* UResourceLoader::Create(UObject* outer)
{
	if (!m_Instance.IsValid())
	{
		if (UResourceLoader* buffer = NewObject<UResourceLoader>(outer))
		{
			m_Instance.Reset(buffer);
		}
		else
		{
			UE_LOG(ResourceLoad, Display, TEXT("Can't create \"ResourceLoader\""))
			return nullptr;
		}
	}

	
	return m_Instance.Get();
}

LoaderHandle& UResourceLoader::ResourceAsyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream, FStreamableDelegate DelegateToCall)
{
	if (!TargetToStream.IsValid())
	{
		UE_LOG(ResourceLoad, Display, TEXT("SoftObjectPath is not valid"));
		return handle;
	}

	const TUniquePtr<UResourceLoader>& instance = UResourceLoader::GetLoaderInstance();
	FScopeLock lock(&instance->m_Mutex);

	if (UAssetManager::IsInitialized())
	{
		const uint64 newID = instance->GetID();
		
		TSharedPtr<FStreamableHandle> loadResource = UAssetManager::GetStreamableManager().RequestAsyncLoad(TargetToStream, FStreamableDelegate::CreateUObject(instance.Get(), &UResourceLoader::OnLoader));
		instance->streamableloading.Emplace(loadResource);
	
		instance->streamableHandler.Add(newID, loadResource);
		handle.id = newID;
	}

	return handle;
}

LoaderHandle& UResourceLoader::ResourceSyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream)
{
	if (!TargetToStream.IsValid())
	{
		UE_LOG(ResourceLoad, Display, TEXT("SoftObjectPath is not valid"));
		return handle;
	}

	if (UAssetManager::IsInitialized())
	{
		const TUniquePtr<UResourceLoader>& instance = UResourceLoader::GetLoaderInstance();
		const uint64 newID = instance->GetID();

		TSharedPtr<FStreamableHandle> loadResource = UAssetManager::GetStreamableManager().RequestSyncLoad(TargetToStream);

		if (loadResource->HasLoadCompleted())
		{
			instance->streamableHandler.Add(newID, loadResource);
		}
		handle.id = newID;
	}
	return handle;
}


const TUniquePtr<UResourceLoader>& UResourceLoader::GetLoaderInstance()
{
	return m_Instance;
}

UObject* UResourceLoader::GetData(const LoaderHandle handler)
{
	if (!m_Instance) return nullptr;

	if (handler.IsValid())
	{
		return UResourceLoader::GetLoaderInstance()->streamableHandler.Find(handler.id)->Get()->GetLoadedAsset();
	}

	return nullptr;
}

void UResourceLoader::OnLoader()
{	
	FScopeLock lock(&m_Mutex);

	TArray<TSharedPtr<FStreamableHandle>> deleteElements;
	for (auto& handler : streamableloading)
	{
		if (handler->HasLoadCompleted())
		{
			OnLoadDelegate.Broadcast(handler->GetLoadedAsset());
			deleteElements.Emplace(handler);
		}
	}

	for (auto& handler : deleteElements)
	{
		streamableloading.Remove(handler);
	}
	deleteElements.Empty();
}

uint64 UResourceLoader::GetID()
{
	return ++IDCounter;
}
