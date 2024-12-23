// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSkillComponent.h"
#include "ClimbSkillComponent.generated.h"



USTRUCT(BlueprintType)
struct FPoint2D
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Z;
};



class AMainPaperCharacter;

UCLASS()
class ROGUELIKE2DGAME_API UClimbSkillComponent : public UBaseSkillComponent
{
	GENERATED_BODY()

public:

	UClimbSkillComponent();

public:

	bool IsClimbing() const;

	const FPoint2D& GetForceJumpOffWall() const;

protected:

	virtual void BeginPlay() override;
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;

	void EnableClimb();
	void DisableClimb();


	UFUNCTION()
	virtual void CheckClimb();

	UFUNCTION()
	void OnLanded(const FHitResult& Hit);

protected:

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float DistanceTrace;

	UPROPERTY(EditAnywhere, meta = (Units = "Seconds", ClampMin = "0.0"))
	float RateCheck;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	float GravityOfCharacterDuringClimb;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"))
	FPoint2D ForceJumpOffWall;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> CollisionCheck;

private:

	AMainPaperCharacter* owningCharacter;
	FTimerHandle TimerHnd;

	float defaultGravity;
	bool hasClimb;
	bool isClimbing;
};
