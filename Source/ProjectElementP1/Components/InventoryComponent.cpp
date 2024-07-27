// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "AbilityComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#if WITH_EDITOR
void UInventoryComponent::AddAbility(TSubclassOf<UAbilityComponent> abilityType)
{
	if (abilityType == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ability type given when adding to ability"));
		return;
	}
	UActorComponent* componentPtr = GetOwner()->AddComponentByClass(abilityType, true, FTransform{}, true);
	m_Abilities.Add(Cast<UAbilityComponent>(componentPtr));
}

void UInventoryComponent::ClearAbilities()
{
	for (auto abilityPtr : m_Abilities)
		abilityPtr->DestroyComponent();
	m_Abilities.Empty();
}
#endif

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

