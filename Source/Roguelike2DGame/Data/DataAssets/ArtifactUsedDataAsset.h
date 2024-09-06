// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ArtifactUsedDataAsset.generated.h"


DECLARE_LOG_CATEGORY_CLASS(LOG_ArtifactDataAasset, Display, Display);

class UBaseArtifactComponent;


USTRUCT(BlueprintType)
struct FDataArtifact
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBaseArtifactComponent* artifact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* icon;
};

UCLASS()
class ROGUELIKE2DGAME_API UArtifactUsedDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void SetIcon(const ESlotArtifact slot, UTexture2D* Texture);

	UFUNCTION(BlueprintPure)
	bool FindArtifact(const FString pahtToArtifact, ESlotArtifact& slot);

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataArtifact rightArtifact;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FDataArtifact leftArtifact;
};
