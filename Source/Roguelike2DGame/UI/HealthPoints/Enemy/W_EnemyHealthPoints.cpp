// Fill out your copyright notice in the Description page of Project Settings.


#include "W_EnemyHealthPoints.h"
#include <Components/ProgressBar.h>



const UProgressBar* UW_EnemyHealthPoints::GetHealthProgressBar()
{
	return PB_Health;
}
