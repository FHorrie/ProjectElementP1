// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ProjectElementP1/Characters/EnemyController.h"
#include "BTT_UseAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTELEMENTP1_API UBTT_UseAbility : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	EAbilityType AbilityType{ EAbilityType::none };
};
