#pragma once

#include "CoreMinimal.h"
#include "InteractInterface.generated.h"



UINTERFACE(MinimalAPI, Blueprintable)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};


class IInteractInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(AActor* interactiveActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OverlapInteract(AActor* interactiveActor);
};