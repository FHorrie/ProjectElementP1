// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "ProjectElementP1/Components/AbilityComponent.h"
#include "EnemyController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityUse, EAbilityType);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityStop, EAbilityType);

UCLASS()
class PROJECTELEMENTP1_API AEnemyController final : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController();
	
	// Delegates
	FOnAbilityUse OnAbilityUse{};
	FOnAbilityStop OnAbilityStop{};
};
