// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeathComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AShiflixCharacter*, character);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTELEMENTP1_API UDeathComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDeathComponent();

	UFUNCTION(BlueprintCallable)
	void Die();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintAssignable)
	FOnDeath DeathDelegate {};
};
