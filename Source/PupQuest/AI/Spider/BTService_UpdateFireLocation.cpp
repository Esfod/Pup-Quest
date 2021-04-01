// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateFireLocation.h"
#include "AIController.h"
#include "PupQuest/Characters/EnemyBaseCharacter.h"
#include "PupQuest/Actors/BrazierActor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "Components/BoxComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateFireLocation::UBTService_UpdateFireLocation()
{
	NodeName = TEXT("Update Location to closest Fire if Fire is seen");
}

void UBTService_UpdateFireLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AEnemyBaseCharacter* OwnerCharacter = Cast<AEnemyBaseCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if(OwnerCharacter == nullptr) return;
	
	OwnerCharacter->CheckFireBox->SetGenerateOverlapEvents(true);
	TArray<AActor*> OverlappingActors;

	float DistanceA {0.f};
	float DistanceB {0.f};
	FVector VectorA {0.f};
	FVector VectorB {0.f};
	OwnerCharacter->CheckFireBox->GetOverlappingActors(OverlappingActors);
	for(AActor* Actor : OverlappingActors)
	{
		if(Actor->IsA(ABrazierActor::StaticClass()))
		{
			ABrazierActor* BrazierActor = Cast<ABrazierActor>(Actor);
			if(BrazierActor == nullptr) return;
			if(OwnerComp.GetAIOwner()->LineOfSightTo(BrazierActor))
			{
				if(BrazierActor->bBrazierActorLit)
                {
					VectorA = BrazierActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
                	DistanceA = VectorA.Size();
                }
			}
		}
		else if(Actor->IsA(ATorchActor::StaticClass()))
		{
			ATorchActor* TorchActor = Cast<ATorchActor>(Actor);
			if(TorchActor == nullptr) return;
			if(OwnerComp.GetAIOwner()->LineOfSightTo(TorchActor))
			{
				if(TorchActor->bTorchLit)
                {
                	VectorA = TorchActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
                	DistanceA = VectorA.Size();
                }
			}		
		}
		if(DistanceA < DistanceB)
		{
			 DistanceB = DistanceA;
			 VectorB = VectorA;
		}	
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), VectorB);
}

