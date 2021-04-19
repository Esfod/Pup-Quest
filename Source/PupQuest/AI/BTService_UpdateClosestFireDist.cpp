// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateClosestFireDist.h"
#include "AIController.h"

#include "PupQuest/Characters/MainCharacter.h"
#include "PupQuest/Characters/EnemyBaseCharacter.h"
#include "PupQuest/Actors/BrazierActor.h"
#include "PupQuest/Actors/TorchHolderActor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"


#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateClosestFireDist::UBTService_UpdateClosestFireDist()
{
	NodeName = TEXT("Update Distanse to closest Fire");
}

void UBTService_UpdateClosestFireDist::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AEnemyBaseCharacter* OwnerCharacter = Cast<AEnemyBaseCharacter>(OwnerComp.GetAIOwner()->GetCharacter());	

	if(OwnerCharacter != nullptr)
	{
		FVector FireLocationVector = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FireLocation.SelectedKeyName);
        
        Distance = FVector(FireLocationVector - OwnerCharacter->GetActorLocation()).Size();
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), Distance);
	}
	else
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	
}