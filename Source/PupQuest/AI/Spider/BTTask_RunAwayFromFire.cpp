// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RunAwayFromFire.h"

#include "PupQuest/Characters/SpiderCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/PawnMovementComponent.h"
#include "NavigationSystem.h"

UBTTask_RunAwayFromFire::UBTTask_RunAwayFromFire()
{
	NodeName = TEXT("Run Away From Fire");
}

EBTNodeResult::Type UBTTask_RunAwayFromFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector FireLocation {0.f};
	FireLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);
	if(FireLocation == FVector{0.f}) return EBTNodeResult::Failed;
	ASpiderCharacter* SpiderCharacter = Cast<ASpiderCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if(SpiderCharacter==nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("SpiderCharacter cast fail"));
		return EBTNodeResult::Failed;
	}
	FVector TempVector = SpiderCharacter->GetActorLocation() - FireLocation;
	TempVector.Normalize();
	SpiderCharacter->MoveForward(TempVector, 1);
	return EBTNodeResult::Succeeded;
}