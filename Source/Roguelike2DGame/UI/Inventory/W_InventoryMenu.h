// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_InventoryMenu.generated.h"




UCLASS()
class ROGUELIKE2DGAME_API UW_InventoryMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;


protected:

	UPROPERTY(EditAnywhere)
	FKey escapeKey;

};
