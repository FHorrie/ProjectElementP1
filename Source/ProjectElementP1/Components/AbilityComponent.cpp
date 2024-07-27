// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"

EAbilityType UAbilityComponent::GetType() const
{
	return Type;
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	checkf(Type != EAbilityType::none, TEXT("No ability selected on %s"), *GetOwner()->GetName());
}
