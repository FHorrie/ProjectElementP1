// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

/**
 * 
 */



UCLASS(Blueprintable, Abstract)
class PROJECTELEMENTP1_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Use();
	UFUNCTION(BlueprintImplementableEvent)
	void Stop();
	UFUNCTION(BlueprintImplementableEvent)
	void Reset();
};
