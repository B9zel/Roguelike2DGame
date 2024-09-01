// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_SwapToEnergyOfSoulsMenu.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE2DGAME_API UW_SwapToEnergyOfSoulsMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

private:

	UPROPERTY(EditAnywhere, meta=(AllowPriveteAccess="true"))
	FKey escapeKey;
};
