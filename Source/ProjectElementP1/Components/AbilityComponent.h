// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AbilityComponent.generated.h"

/**
 * 
 */

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

UCLASS()
class PROJECTELEMENTP1_API UAbilityComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	virtual void Use() PURE_VIRTUAL();
	virtual void Stop() PURE_VIRTUAL();
	virtual void Reset() PURE_VIRTUAL();

	EAbilityType GetType() const;

protected:
	virtual void BeginPlay() override;
	
private:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	EAbilityType Type{ EAbilityType::none };
};
