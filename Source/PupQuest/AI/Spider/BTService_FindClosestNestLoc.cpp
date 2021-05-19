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
	AEnemyBaseCharacter* EnemyBaseCharacter = Cast<AEnemyBaseCharacter>(OwnerComp.GetAIOwner()->GetPawn()); //cast the owner of the Aicontroller
	TArray<AEnemyNestActor*> EnemyNests = EnemyBaseCharacter->GetEnemyNestActors(); //gets all the nests close too the spider
	if(EnemyNests.Num() == 0) //Checks if there are non nests
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		UE_LOG(LogTemp,Warning,TEXT("%s has no Nests"),*OwnerComp.GetName());
		return; //stops the hole function
	}

	const FVector EnemyLocation = EnemyBaseCharacter->GetActorLocation(); //gets the location of the spider
	FVector VectorA {0.f};
	FVector VectorB {0.f};
	FVector ClosestNestLoc {0.f};
	
	for (AEnemyNestActor* Nest : EnemyNests) //goes through every nest and finds the distance to it and saves the location of it
	{
		if(Nest == nullptr) return;
		VectorA = EnemyLocation - Nest->GetActorLocation();
		if(VectorB.Size() == 0.f || VectorA.Size() <= VectorB.Size())
		{
			VectorB = VectorA;
			ClosestNestLoc = Nest->GetActorLocation();
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ClosestNestLoc); //sends the location of the closest nest to the BehaviorTree
}
