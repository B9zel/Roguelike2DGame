<<<<<<< HEAD
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EnemyHealthPoints.generated.h"



class UProgressBar;
class UHealthComponent;

UCLASS()
class ROGUELIKE2DGAME_API UW_EnemyHealthPoints : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	UFUNCTION()
	float BindPercentHealth();

protected:
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UProgressBar* PB_Health;

	UHealthComponent* healthBind;
public:

	const UProgressBar* GetHealthProgressBar();

	void SetHealthComponentBind(UHealthComponent* component);
};
=======
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EnemyHealthPoints.generated.h"



class UProgressBar;

UCLASS()
class ROGUELIKE2DGAME_API UW_EnemyHealthPoints : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* PB_Health;
public:

	const UProgressBar* GetHealthProgressBar();
};
>>>>>>> ff07792bbfedc3c9bb8c7def60ebb4fe45bc5ba7
