// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "ProjectElementP1/Components/EquipmentComponent.h"
#include "EnemyController.generated.h"

class UCrowdFollowingComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityUse, EAbilitySlot);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityStop, EAbilitySlot);

UCLASS()
class PROJECTELEMENTP1_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	// Delegates
	FOnAbilityUse OnAbilityUse{};
	FOnAbilityStop OnAbilityStop{};

private:
	UPROPERTY()
	UCrowdFollowingComponent* CrowdFollowingComponent{};
};
