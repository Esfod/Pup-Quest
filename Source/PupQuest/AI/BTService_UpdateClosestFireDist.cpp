// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateClosestFireDist.h"
#include "AIController.h"
#include "PupQuest/Characters/EnemyBaseCharacter.h"
#include "PupQuest/Actors/BrazierActor.h"
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
	if(OwnerCharacter == nullptr) return;
	
	TArray<AActor*> OverlappingActors =  OwnerCharacter->GetOverLappingActorsToFireBox();

	float DistanceA {0.f};
	float DistanceB {0.f};
	
	for(AActor* Actor : OverlappingActors)
	{
		if(Actor->IsA(ABrazierActor::StaticClass()))
		{
			ABrazierActor* BrazierActor = Cast<ABrazierActor>(Actor);
			if(BrazierActor == nullptr) return;
			if(BrazierActor->bBrazierActorLit)
			{
				DistanceA = FVector(BrazierActor->GetActorLocation() - OwnerCharacter->GetActorLocation()).Size();
			}
		}
		else if(Actor->IsA(ATorchActor::StaticClass()))
		{
			ATorchActor* TorchActor = Cast<ATorchActor>(Actor);
			if(TorchActor == nullptr) return;
			if(TorchActor->bTorchLit)
			{
				DistanceA = FVector(TorchActor->GetActorLocation() - OwnerCharacter->GetActorLocation()).Size();
			}
		}
		if(DistanceA < DistanceB)
			DistanceA = DistanceB;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), DistanceB);
}