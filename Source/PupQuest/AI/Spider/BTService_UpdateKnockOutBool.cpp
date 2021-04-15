// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateKnockOutBool.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PupQuest/Characters/SpiderCharacter.h"
#include "AIController.h"
UBTService_UpdateKnockOutBool::UBTService_UpdateKnockOutBool()
{
	NodeName = TEXT("Update KnockOut Bool");
}

void UBTService_UpdateKnockOutBool::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	ASpiderCharacter* OwnerCharacter = Cast<ASpiderCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if(OwnerCharacter == nullptr)
	{
		UE_LOG(LogTemp,Warning, TEXT("Spider Cast Failed, i UBTService_UpdateKnockOutBool()"))
	}
	//if (OwnerCharacter->bIsEnemyKnockedOut)
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), 0);
	//else
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), 1);
}
