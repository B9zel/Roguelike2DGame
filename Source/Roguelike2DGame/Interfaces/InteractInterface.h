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


class IInteract
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AActor* interactiveActor);

};


class IOverlapInteract
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OverlapInteract(AActor* interactiveActor);
};