// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryHandlerComponent.generated.h"

enum class EAbilitySlot : uint8;
class UAbilityComponent;

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()
	
	bool operator==(const FInventorySlot& other) const;
	bool operator==(TSubclassOf<UAbilityComponent> type) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString displayName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<UAbilityComponent> abilityType {nullptr };
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EAbilitySlot abilitySlot{};
	int32_t nrUpgradeTokens{};
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewAbilityCollect, const FInventorySlot&, slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityCollect, const FInventorySlot&, slot);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTELEMENTP1_API UInventoryHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryHandlerComponent();
	
	UFUNCTION(BlueprintCallable)
	void AddAbility(const FString& displayName, TSubclassOf<UAbilityComponent> abilityType, EAbilitySlot abilitySlot);

	UFUNCTION(BlueprintCallable)
	bool HasAbility(TSubclassOf<UAbilityComponent> abilityType) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintAssignable)
	FOnNewAbilityCollect NewAbilityDelegate {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintAssignable)
	FOnAbilityCollect AbilityDelegate {};

private:
	TArray<FInventorySlot> m_Slots{};
};
