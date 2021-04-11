// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpiderAttack.h"
#include "AIController.h"
#include "PupQuest/Characters/EnemyBaseCharacter.h"

UBTTask_SpiderAttack::UBTTask_SpiderAttack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_SpiderAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyBaseCharacter* SpiderCharacter = Cast<AEnemyBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(SpiderCharacter == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("cast failed"));
		return EBTNodeResult::Failed;
	}
	SpiderCharacter->Attack(SpiderCharacter->Damage);
	return EBTNodeResult::Succeeded;
}
