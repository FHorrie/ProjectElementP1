// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectElementP1/Components/AbilityComponent.h"
#include "EquipmentComponent.generated.h"


UENUM(BlueprintType, meta=(Bitflags))
enum class EAbilitySlot : uint8 
{
	leftArm UMETA(DisplayName = "Left arm"),
	rightArm UMETA(DisplayName = "Right arm"),
	leftLeg UMETA(DisplayName = "Left leg"),
	rightLeg UMETA(DisplayName = "Right leg"),
	head UMETA(DisplayName = "Head"),
	NR_ABILITIES UMETA(Hidden),
	none UMETA(DisplayName = "None")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAbilitySwitch, TSubclassOf<UAbilityComponent>, abilityType, EAbilitySlot, abilitySlot, const FString&, displayName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityCooldown, EAbilitySlot, abilitySlot, float, cooldownTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityCooldownReset, EAbilitySlot, abilitySlot);

class UAbilityComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTELEMENTP1_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentComponent();

	UFUNCTION(BlueprintCallable)
	void SwitchAbility(EAbilitySlot abilitySlot, TSubclassOf<UAbilityComponent> abilityType);
	UFUNCTION(BlueprintCallable)
	void UseAbility(EAbilitySlot abilitySlot);
	UFUNCTION(BlueprintCallable)
	void StopAbility(EAbilitySlot abilitySlot);

	UFUNCTION(BlueprintCallable)
	UAbilityComponent* GetAbility(EAbilitySlot abilitySlot) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintAssignable)
	FOnAbilitySwitch AbilitySwitchDelegate {};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintAssignable)
	FOnAbilitySwitch AbilityCreateDelegate {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintAssignable)
	FOnAbilityCooldown AbilityCooldownDelegate{};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, BlueprintAssignable)
	FOnAbilityCooldownReset AbilityCooldownResetDelegate{};
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UAbilityComponent* CreateAbility(TSubclassOf<UAbilityComponent> abilityType, EAbilitySlot abilitySlot) const;
	UFUNCTION()
	void HandleCooldown(float cooldownTime, UAbilityComponent* abilityPtr);
	UFUNCTION()
	void HandleCooldownReset(UAbilityComponent* abilityPtr);

	bool IsSlotValid(EAbilitySlot abilitySlot) const;
	EAbilitySlot GetSlot(UAbilityComponent* abilityPtr) const;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<TSubclassOf<UAbilityComponent>> AbilityTypes{};

	UPROPERTY()
	TArray<UAbilityComponent*> m_Abilities{};
};
