// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathComponent.h"

#include "ProjectElementP1/Characters/ShiflixCharacter.h"


// Sets default values for this component's properties
UDeathComponent::UDeathComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDeathComponent::Die()
{
	if (AShiflixCharacter* shiflexPtr = Cast<AShiflixCharacter>(GetOwner()))
		DeathDelegate.Broadcast(shiflexPtr);
}
