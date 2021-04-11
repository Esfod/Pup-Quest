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
	if(OwnerCharacter == nullptr) return;
	
	TArray<AActor*> OverlappingActors =  OwnerCharacter->GetOverLappingActorsToFireBox();

	float DistanceA {0.f};
	float DistanceB {0.f};
	for(AActor* Actor : OverlappingActors)
	{
		//UE_LOG(LogTemp,Warning,TEXT("%s"), *Actor->GetName());
		if(OwnerComp.GetAIOwner()->LineOfSightTo(Actor))
		{
			if(Actor->IsA(AMainCharacter::StaticClass()))
			{
				//UE_LOG(LogTemp,Warning,TEXT("Sees Actor"))
				AMainCharacter* MainCharacter = Cast<AMainCharacter>(Actor);
				if(MainCharacter->bHoldingTorch)
				{
					if(MainCharacter->bTorchLit)
					{
						DistanceA = FVector(MainCharacter->GetActorLocation() - OwnerCharacter->GetActorLocation()).Size();
						//UE_LOG(LogTemp,Warning,TEXT("2. Distance A = %f\tDistance B = %f"), DistanceA, DistanceB);
					}
				}
			}
			else if(Actor->IsA(ATorchHolderActor::StaticClass()))
			{
				ATorchHolderActor* TorchHolderActor = Cast<ATorchHolderActor>(Actor);
				if(TorchHolderActor)
				{
					if(TorchHolderActor->bHasATorch)
					{
						DistanceA = FVector(TorchHolderActor->GetActorLocation() - OwnerCharacter->GetActorLocation()).Size();
						//UE_LOG(LogTemp,Warning,TEXT("2. Distance A = %f\tDistance B = %f"), DistanceA, DistanceB);
					}
				}
			}
			else if(Actor->IsA(ABrazierActor::StaticClass()))
			{
				ABrazierActor* BrazierActor = Cast<ABrazierActor>(Actor);
				if(BrazierActor)
				{
					if(BrazierActor->bBrazierLit)
					{
						DistanceA = FVector(BrazierActor->GetActorLocation() - OwnerCharacter->GetActorLocation()).Size();
					}
				}
			}
			else if(Actor->IsA(ATorchActor::StaticClass()))
			{
				ATorchActor* TorchActor = Cast<ATorchActor>(Actor);
				if(TorchActor)
				{
					if(TorchActor->bTorchLit)
					{
						DistanceA = FVector(TorchActor->GetActorLocation() - OwnerCharacter->GetActorLocation()).Size();
					}
				}
			}
			if(DistanceA < DistanceB)
				DistanceB = DistanceA;
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), DistanceB);
}