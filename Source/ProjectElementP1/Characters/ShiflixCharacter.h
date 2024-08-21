// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShiflixCharacter.generated.h"

class UEquipmentComponent;

UCLASS()
class PROJECTELEMENTP1_API AShiflixCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShiflixCharacter();
	
	virtual void PossessedBy(AController* NewController) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UEquipmentComponent* Equipment{ nullptr };
};
