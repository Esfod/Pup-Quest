// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "PupQuest/Characters/SpiderCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ASpiderCharacter* SpiderCharacter = Cast<ASpiderCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if(SpiderCharacter == nullptr) return EBTNodeResult::Failed;

	SpiderCharacter->Attack();
	return EBTNodeResult::Succeeded;
}
