// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "Navigation/CrowdFollowingComponent.h"


AEnemyController::AEnemyController(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	CrowdFollowingComponent = CreateDefaultSubobject<UCrowdFollowingComponent>(TEXT("CrowdComponent"));
}
