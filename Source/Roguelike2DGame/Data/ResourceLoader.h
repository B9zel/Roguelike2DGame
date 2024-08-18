// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/StreamableManager.h"
#include "ResourceLoader.generated.h"



class UObject;
class UResourceLoader;

struct FStreamableHandle;

DECLARE_MULTICAST_DELEGATE_OneParam(FLoaderDelegate, UObject*);
DECLARE_LOG_CATEGORY_CLASS(ResourceLoad, Display, Display);


struct LoaderHandle
{
public:

	friend UResourceLoader;

public:

	LoaderHandle() = default;

	bool IsValid() const
	{
		return id != 0;
	}

private:

	uint64 id = 0;
};


UCLASS()
class ROGUELIKE2DGAME_API UResourceLoader : public UObject
{

	GENERATED_BODY()

public:
	
	static UResourceLoader* Create(UObject* outer);
	static LoaderHandle& ResourceAsyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream, FStreamableDelegate DelegateToCall);
	static LoaderHandle& ResourceSyncLoad(LoaderHandle& handle, const FSoftObjectPath& TargetToStream);
	static const TUniquePtr<UResourceLoader>& GetLoaderInstance();
	static UObject* GetData(const LoaderHandle handler);

private:

	UResourceLoader() = default;

private:

	void OnLoader();
	uint64 GetID();

private:

	FLoaderDelegate OnLoadDelegate;
	
	
	TMap<uint64, TSharedPtr<FStreamableHandle>> streamableHandler;
	TArray<TSharedPtr<FStreamableHandle>> streamableloading;

	static uint64 IDCounter;
	static TUniquePtr<UResourceLoader> m_Instance;

	FCriticalSection m_Mutex;
};

