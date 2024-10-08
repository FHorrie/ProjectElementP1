﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

/**
 * 
 */

class PROJECTELEMENTP1_API UAbilityComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCooldown, float, cooldownTime, UAbilityComponent*, abilityPtr);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCooldownReset, UAbilityComponent*, abilityPtr);

UCLASS(Blueprintable, Abstract)
class PROJECTELEMENTP1_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbilityComponent();
	
	void HandleUse();
	void HandleStop();
	
	const FString& GetAbilityName() const;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	FOnCooldown CooldownDelegate{};
	FOnCooldownReset CooldownResetDelegate{};

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Use();
	UFUNCTION(BlueprintImplementableEvent)
	void Stop();
	UFUNCTION(BlueprintNativeEvent)
	void Reset();
	
private:
	void ActivateCooldown();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FString Name{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float Cooldown{ 0.0f };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool CooldownOnUse{ true };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool CooldownOnStop{ true };

	FTimerHandle m_CooldownHandle{};
	bool m_AllowUse{ true };
	bool m_WasUsed{ false };
};
