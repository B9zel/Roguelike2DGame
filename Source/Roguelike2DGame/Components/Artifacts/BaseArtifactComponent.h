// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseArtifactComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROGUELIKE2DGAME_API UBaseArtifactComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UBaseArtifactComponent();
		
};
