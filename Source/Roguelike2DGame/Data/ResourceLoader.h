// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/StreamableManager.h"




class UObject;
class ResourceLoader;

struct FStreamableHandle;


DECLARE_MULTICAST_DELEGATE_OneParam(FLoaderDelegate, UObject*);
DECLARE_LOG_CATEGORY_CLASS(LogResourceLoad, Display, Display);


struct LoaderHandle
{
public:

	friend ResourceLoader;

public:

	LoaderHandle() = default;

	bool IsValid() const
	{
		return id != 0;
	}

private:

	uint64 id = 0;
};


class ROGUELIKE2DGAME_API ResourceLoader
{

public:
	
	static ResourceLoader* Create();
	static LoaderHandle& ResourceAsyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream, FStreamableDelegate DelegateToCall);
	static LoaderHandle& ResourceSyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream);
	static const TUniquePtr<ResourceLoader>& GetLoaderInstance();
	static UObject* GetData(const LoaderHandle handler);

	void ClearData();
	void DestroyLoader();

private:

	ResourceLoader() = default;

private:

	void OnLoader();
	uint64 GetID();

private:


	FLoaderDelegate OnLoadDelegate;
	
	TMap<uint64, TSharedPtr<FStreamableHandle>> streamableHandler;
	// Used for async load
	TMap<TSharedPtr<FStreamableHandle>, LoaderHandle*> streamableLoading;
	//
	uint64 IDCounter;
	FCriticalSection m_Mutex;

	static TUniquePtr<ResourceLoader> m_Instance;
};

