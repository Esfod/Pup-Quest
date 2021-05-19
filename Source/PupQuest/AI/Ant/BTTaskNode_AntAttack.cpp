// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_AntAttack.h"
#include "PupQuest/Characters/AntCharacter.h"
#include "AIController.h"

UBTTaskNode_AntAttack::UBTTaskNode_AntAttack()
{
	NodeName = TEXT("Ant Attack");
}

EBTNodeResult::Type UBTTaskNode_AntAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAntCharacter* AntCharacter = Cast<AAntCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if(AntCharacter == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("cast failed"));
		return EBTNodeResult::Failed; //tells the behaviorthree that the task was a fail
	}
	AntCharacter->Attack(); //runs attack from ant character class, and get's damage
	return EBTNodeResult::Succeeded; //tells the behaviorthree that the task was a success
}
