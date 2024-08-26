// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHandlerComponent.h"

#include "AbilityComponent.h"

bool FInventorySlot::operator==(const FInventorySlot& other) const
{
	return other.abilitySlot == abilitySlot;
}

bool FInventorySlot::operator==(TSubclassOf<UAbilityComponent> type) const
{
	return type == abilityType;
}

// Sets default values for this component's properties
UInventoryHandlerComponent::UInventoryHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryHandlerComponent::AddAbility(const FString& displayName, TSubclassOf<UAbilityComponent> abilityType, EAbilitySlot abilitySlot)
{
	check(abilityType != nullptr);

	FInventorySlot slot{};
	slot.displayName = displayName;
	slot.abilityType = abilityType;
	slot.abilitySlot = abilitySlot;
	if (!HasAbility(abilityType))
	{
		NewAbilityDelegate.Broadcast(slot);
		AbilityDelegate.Broadcast(slot);
		m_Slots.Add(slot);
	}
	else
	{
		FInventorySlot* foundSlot{ m_Slots.FindByPredicate([abilityType](const FInventorySlot& slot)
		{
			return slot.abilityType == abilityType;
		}) };
		++foundSlot->nrUpgradeTokens;
		AbilityDelegate.Broadcast(*foundSlot);
	}
}

bool UInventoryHandlerComponent::HasAbility(TSubclassOf<UAbilityComponent> abilityType) const
{
	return m_Slots.Contains(abilityType);
}
