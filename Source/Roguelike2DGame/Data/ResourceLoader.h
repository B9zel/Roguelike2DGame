// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/StreamableManager.h"

class ResourceLoader;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoaderDeligate, class UObject*, objectLoader)

struct LoaderHandle
{
public:

	friend ResourceLoader;

public:

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
	
	static const TUniquePtr<ResourceLoader>& Create();
	static LoaderHandle& ResourceAsyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream, FStreamableDelegate DelegateToCall);
	static const TUniquePtr<ResourceLoader>& GetLoaderInstance();
	const TSharedPtr<FStreamableHandle>& GetData(const LoaderHandle& handler);

private:

	ResourceLoader() = default;

private:

	void OnLoader();

	uint64 GetID();

private:

	FLoaderDeligate OnLoadDelegate;

	TMap<uint64, TSharedPtr<FStreamableHandle>> streamableHandler;
	TArray<TSharedPtr<FStreamableHandle>> streamableloading;

	static uint64 IDCounter;
	static TUniquePtr<ResourceLoader> m_Instance;
};

