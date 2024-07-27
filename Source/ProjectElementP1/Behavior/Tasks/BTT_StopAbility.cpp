// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_StopAbility.h"

EBTNodeResult::Type UBTT_StopAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyController* controllerPtr = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	if (controllerPtr == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't stop the ability of %s"), *OwnerComp.GetAIOwner()->GetName());
		return EBTNodeResult::Failed;
	}

	controllerPtr->OnAbilityStop.Broadcast(AbilityType);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

