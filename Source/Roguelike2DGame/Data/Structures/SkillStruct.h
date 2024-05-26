// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillStruct.generated.h"


USTRUCT(BlueprintType)
struct FSkillStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* niagaraSystem;
};


//UCLASS()
//class ROGUELIKE2DGAME_API USkillStruct : public UObject
//{
//	GENERATED_BODY()
//	
//};
