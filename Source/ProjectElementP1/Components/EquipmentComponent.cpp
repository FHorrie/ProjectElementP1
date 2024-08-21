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
	const uint8 abilityNr{ static_cast<uint8>(abilitySlot) };
	AbilityTypes[abilityNr] = abilityType;
	StopAbility(abilitySlot);
	if (m_Abilities[abilityNr] != nullptr)
		m_Abilities[abilityNr]->DestroyComponent();
	m_Abilities[abilityNr] = CreateAbility(abilityType);
}

void UEquipmentComponent::UseAbility(EAbilitySlot abilitySlot)
{
	if (IsSlotValid(abilitySlot))
		GetAbility(abilitySlot)->Use();
}

void UEquipmentComponent::StopAbility(EAbilitySlot abilitySlot)
{
	if (!IsSlotValid(abilitySlot))
		return;

	UAbilityComponent* abilityPtr{ GetAbility(abilitySlot) };
	abilityPtr->Stop();
	abilityPtr->Reset();
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
	for (auto abilityType : AbilityTypes)
		m_Abilities.Add(CreateAbility(abilityType));
}

UAbilityComponent* UEquipmentComponent::CreateAbility(TSubclassOf<UAbilityComponent> abilityType) const
{
	if (abilityType == nullptr)
		return nullptr;
	UAbilityComponent* abilityPtr{ NewObject<UAbilityComponent>(GetOwner(), abilityType.Get()) };
	abilityPtr->RegisterComponent();
	return abilityPtr;
}

bool UEquipmentComponent::IsSlotValid(EAbilitySlot abilitySlot) const
{
	const uint8 slotNr{ static_cast<uint8>(abilitySlot) };
	if (abilitySlot > EAbilitySlot::NR_ABILITIES)
		return false;
	return m_Abilities[slotNr] != nullptr;
}

UAbilityComponent* UEquipmentComponent::GetAbility(EAbilitySlot abilitySlot) const
{
	return m_Abilities[static_cast<uint8>(abilitySlot)];
}


