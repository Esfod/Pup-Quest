// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindClosestNestLoc.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

#include "PupQuest/Characters/EnemyBaseCharacter.h"
#include "PupQuest/Actors/EnemyNestActor.h"

UBTService_FindClosestNestLoc::UBTService_FindClosestNestLoc()
{
	NodeName = "Update Closest Nest Location";
}

void UBTService_FindClosestNestLoc::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AEnemyBaseCharacter* EnemyBaseCharacter = Cast<AEnemyBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	TArray<AEnemyNestActor*> EnemyNests = EnemyBaseCharacter->GetEnemyNestActors();
	if(EnemyNests.Num() == 0)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		UE_LOG(LogTemp,Warning,TEXT("%s has no Nests PLEASE FIX"),*OwnerComp.GetName());
		return;
	}

	const FVector EnemyLocation = EnemyBaseCharacter->GetActorLocation();
	FVector VectorA {0.f};
	FVector VectorB {0.f};
	FVector ClosestNestLoc {0.f};
	
	for (AEnemyNestActor* Nest : EnemyNests)
	{
		if(Nest == nullptr) return;
		VectorA = EnemyLocation - Nest->GetActorLocation();
		if(VectorB.Size() == 0.f || VectorA.Size() <= VectorB.Size())
		{
			VectorB = VectorA;
			ClosestNestLoc = Nest->GetActorLocation();
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ClosestNestLoc);

}
