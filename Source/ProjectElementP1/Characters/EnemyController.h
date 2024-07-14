// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "EnemyController.generated.h"

UENUM(BlueprintType)
enum class EAbilityType : uint8 
{
	none UMETA(DisplayName = "None"),
	leftArm UMETA(DisplayName = "Left arm"),
	rightArm UMETA(DisplayName = "Right arm"),
	leftLeg UMETA(DisplayName = "Left leg"),
	rightLeg UMETA(DisplayName = "Right leg"),
	head UMETA(DisplayName = "Head")
};

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
