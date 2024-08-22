// Fill out your copyright notice in the Description page of Project Settings.


#include "ShiflixCharacter.h"

#include "EnemyController.h"
#include "ProjectElementP1/Components/DeathComponent.h"
#include "ProjectElementP1/Components/EquipmentComponent.h"


// Sets default values
AShiflixCharacter::AShiflixCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));
	DeathHandler = CreateDefaultSubobject<UDeathComponent>(TEXT("DeathHandler"));
}

void AShiflixCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AEnemyController* controllerPtr = Cast<AEnemyController>(NewController))
	{
		controllerPtr->OnAbilityUse.AddUObject(Equipment, &UEquipmentComponent::UseAbility);
		controllerPtr->OnAbilityStop.AddUObject(Equipment, &UEquipmentComponent::StopAbility);
	}
}
