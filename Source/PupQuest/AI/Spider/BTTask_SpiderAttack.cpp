// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SpiderAttack.h"
#include "AIController.h"
#include "PupQuest/Characters/SpiderCharacter.h"

UBTTask_SpiderAttack::UBTTask_SpiderAttack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_SpiderAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ASpiderCharacter* SpiderCharacter = Cast<ASpiderCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(SpiderCharacter == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("cast failed"));
		return EBTNodeResult::Failed;					//tells the behaviorthree that the task was a fail
	}
	SpiderCharacter->Attack();	//runs attack from ant character class, and get's damage
	return EBTNodeResult::Succeeded;					//tells the behaviorthree that the task was a success
}