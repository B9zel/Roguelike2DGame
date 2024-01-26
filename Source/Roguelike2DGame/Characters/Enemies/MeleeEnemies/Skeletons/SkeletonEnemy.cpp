// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletonEnemy.h"


void ASkeletonEnemy::OnAttack()
{
	if (canAttack)
	{
		AMeleeEnemy::OnAttack();


	}
}

