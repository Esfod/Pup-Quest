// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attac.h"
#include "AIController.h"
#include "PupQuest/Characters/EnemyBaseCharacter.h"
#include "PupQuest/Characters/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTTask_Attac::UBTTask_Attac()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attac::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemyBaseCharacter* SpiderCharacter = Cast<AEnemyBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	//AMainCharacter* MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if(SpiderCharacter == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("cast failed"));
		return EBTNodeResult::Failed;
	}
	SpiderCharacter->Attack(SpiderCharacter->Damage);
	return EBTNodeResult::Succeeded;
}
