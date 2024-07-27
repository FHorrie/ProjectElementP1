// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_UseAbility.h"

EBTNodeResult::Type UBTT_UseAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyController* controllerPtr = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	if (controllerPtr == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't use the ability of %s"), *OwnerComp.GetAIOwner()->GetName());
		return EBTNodeResult::Failed;
	}

	controllerPtr->OnAbilityUse.Broadcast(AbilityType);
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
