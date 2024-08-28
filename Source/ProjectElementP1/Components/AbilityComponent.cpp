// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAbilityComponent::HandleUse()
{
	if (!m_AllowUse)
		return;

	Use();
	
	m_WasUsed = true;
}

void UAbilityComponent::HandleStop()
{
	if (!m_WasUsed)
		return;
	
	Stop();
	
	m_WasUsed = false;
	if (CooldownOnStop)
		ActivateCooldown();
	else
		Reset();
}

const FString& UAbilityComponent::GetAbilityName() const
{
	return Name;
}

void UAbilityComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	m_CooldownHandle.Invalidate();
}

void UAbilityComponent::Reset_Implementation()
{
	m_CooldownHandle.Invalidate();
	m_AllowUse = true;
}

void UAbilityComponent::ActivateCooldown()
{
	if (Cooldown < FLT_EPSILON)
		return;

	if (m_CooldownHandle.IsValid())
		m_CooldownHandle.Invalidate();

	CooldownDelegate.Broadcast(Cooldown, this);
	
	m_AllowUse = false;
	FTimerDelegate delegate{};
	delegate.BindLambda([this]()
	{
		this->Reset();
		this->CooldownResetDelegate.Broadcast(this);
	});
	
	GetWorld()->GetTimerManager().SetTimer(m_CooldownHandle, delegate, Cooldown, false, Cooldown);
}
