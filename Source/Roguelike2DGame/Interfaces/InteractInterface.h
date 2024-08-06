#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.generated.h"



UINTERFACE(MinimalAPI, Blueprintable)
class UInteract : public UInterface
{
	GENERATED_BODY()
};

UINTERFACE(MinimalAPI, Blueprintable)
class UOverlapInteract : public UInterface
{
	GENERATED_BODY()
};


class ROGUELIKE2DGAME_API IInteract
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AActor* interactiveActor);

};


class ROGUELIKE2DGAME_API IOverlapInteract
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OverlapInteract(AActor* interactiveActor);
};