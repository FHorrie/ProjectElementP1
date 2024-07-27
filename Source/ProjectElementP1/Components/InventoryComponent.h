// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectElementP1/Components/AbilityComponent.h"
#include "InventoryComponent.generated.h"


class UAbilityComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTELEMENTP1_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

#if WITH_EDITOR
	UFUNCTION(CallInEditor, BlueprintCallable)
	void AddAbility(TSubclassOf<UAbilityComponent> abilityType);
	UFUNCTION(CallInEditor, BlueprintCallable)
	void ClearAbilities();
#endif
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	EAbilityType Type{ EAbilityType::none };

private:
	
	UPROPERTY()
	TArray<UAbilityComponent*> m_Abilities{};
};
