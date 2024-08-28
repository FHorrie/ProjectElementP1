// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

#include "AbilityComponent.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	constexpr uint8 nrAbilities{ static_cast<uint8>(EAbilitySlot::NR_ABILITIES) };
	AbilityTypes.SetNum(nrAbilities);
}

void UEquipmentComponent::SwitchAbility(EAbilitySlot abilitySlot, TSubclassOf<UAbilityComponent> abilityType)
{
	if (abilitySlot > EAbilitySlot::NR_ABILITIES || abilityType == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ability entered on %s"), *GetOwner()->GetName());
		return;
	}
	
	const uint8 abilityNr{ static_cast<uint8>(abilitySlot) };
	AbilityTypes[abilityNr] = abilityType;
	StopAbility(abilitySlot);
	if (m_Abilities[abilityNr] != nullptr)
		m_Abilities[abilityNr]->DestroyComponent();
	m_Abilities[abilityNr] = CreateAbility(abilityType, abilitySlot);

	AbilitySwitchDelegate.Broadcast(abilityType, abilitySlot, m_Abilities[abilityNr]->GetAbilityName());
}

void UEquipmentComponent::UseAbility(EAbilitySlot abilitySlot)
{
	if (IsSlotValid(abilitySlot))
		GetAbility(abilitySlot)->HandleUse();
}

void UEquipmentComponent::StopAbility(EAbilitySlot abilitySlot)
{
	if (!IsSlotValid(abilitySlot))
		return;

	UAbilityComponent* abilityPtr{ GetAbility(abilitySlot) };
	abilityPtr->HandleStop();
}

// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// Check if the dev has enough abilities
	constexpr uint8 nrAbilities{ static_cast<uint8>(EAbilitySlot::NR_ABILITIES) };
	if (AbilityTypes.Num() < nrAbilities)
	{
		AbilityTypes.SetNum(nrAbilities);
		UE_LOG(LogTemp, Warning, TEXT("Not enough abilities found in %s"), *GetOwner()->GetName());
	}
	
	// Fill abilities up
	m_Abilities.Empty();
	int idx{};
	for (auto abilityType : AbilityTypes)
	{
		const EAbilitySlot slot{ static_cast<EAbilitySlot>(idx) };
		UAbilityComponent* abilityPtr{ CreateAbility(abilityType, slot) };
		m_Abilities.Add(abilityPtr);
		if(abilityPtr != nullptr)
			AbilityCreateDelegate.Broadcast(abilityType, slot, abilityPtr->GetAbilityName());
		++idx;
	}
		
}

UAbilityComponent* UEquipmentComponent::CreateAbility(TSubclassOf<UAbilityComponent> abilityType, EAbilitySlot abilitySlot) const
{
	if (abilityType == nullptr)
		return nullptr;
	UAbilityComponent* abilityPtr{ NewObject<UAbilityComponent>(GetOwner(), abilityType.Get()) };
	abilityPtr->RegisterComponent();
	abilityPtr->CooldownDelegate.AddDynamic(this, &UEquipmentComponent::HandleCooldown);
	abilityPtr->CooldownResetDelegate.AddDynamic(this, &UEquipmentComponent::HandleCooldownReset);
	return abilityPtr;
}

void UEquipmentComponent::HandleCooldown(float cooldownTime, UAbilityComponent* abilityPtr)
{
	const EAbilitySlot slot{ GetSlot(abilityPtr) };
	if (slot == EAbilitySlot::none)
		return;
	AbilityCooldownDelegate.Broadcast(slot, cooldownTime);
}

void UEquipmentComponent::HandleCooldownReset(UAbilityComponent* abilityPtr)
{
	const EAbilitySlot slot{ GetSlot(abilityPtr) };
	if (slot == EAbilitySlot::none)
		return;
	AbilityCooldownResetDelegate.Broadcast(slot);
}

bool UEquipmentComponent::IsSlotValid(EAbilitySlot abilitySlot) const
{
	const uint8 slotNr{ static_cast<uint8>(abilitySlot) };
	if (abilitySlot > EAbilitySlot::NR_ABILITIES)
		return false;
	return m_Abilities[slotNr] != nullptr;
}

EAbilitySlot UEquipmentComponent::GetSlot(UAbilityComponent* abilityPtr) const
{
	const int idx{ m_Abilities.Find(abilityPtr) };
	return (idx == -1) ? EAbilitySlot::none : static_cast<EAbilitySlot>(idx);
}

UAbilityComponent* UEquipmentComponent::GetAbility(EAbilitySlot abilitySlot) const
{
	if (m_Abilities.IsEmpty())
		return nullptr;
	return m_Abilities[static_cast<uint8>(abilitySlot)];
}


