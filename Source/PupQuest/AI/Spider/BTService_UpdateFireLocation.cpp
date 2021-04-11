// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateFireLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

#include "PupQuest/Characters/MainCharacter.h"
#include "PupQuest/Characters/EnemyBaseCharacter.h"
#include "PupQuest/Actors/BrazierActor.h"
#include "PupQuest/Actors/TorchHolderActor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"



UBTService_UpdateFireLocation::UBTService_UpdateFireLocation()
{
	NodeName = TEXT("Update Location to closest Fire if Fire is seen");
}

void UBTService_UpdateFireLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AEnemyBaseCharacter* OwnerCharacter = Cast<AEnemyBaseCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if(OwnerCharacter == nullptr) return;
	TArray<AActor*> OverlappingActors = OwnerCharacter->GetOverLappingActorsToFireBox();
	float DistanceA {0.f}; //an temporary variable
	float DistanceB {100000.f}; 
	FVector DistacnceVector {0.f}; //an temporary variable
	FVector VectorA {0.f};
	FVector VectorB {0.f}; //the outgoing variable
	bool bDistanceASet {false};
	//UE_LOG(LogTemp,Warning,TEXT("1. Distance A = %f\tDistance B = %f"), DistanceA, DistanceB);

	for(AActor* Actor : OverlappingActors)
	{
		//UE_LOG(LogTemp,Warning,TEXT("%s"), *Actor->GetName());
		if(OwnerComp.GetAIOwner()->LineOfSightTo(Actor))
		{
			if(Actor->IsA(ABrazierActor::StaticClass()))
			{
				ABrazierActor* BrazierActor = Cast<ABrazierActor>(Actor);
				if(BrazierActor == nullptr) return;
				if(OwnerComp.GetAIOwner()->LineOfSightTo(BrazierActor))
				{
					if(BrazierActor->bBrazierLit)
					{
						//UE_LOG(LogTemp,Warning,TEXT("Can see lit Brazier"));
						DistacnceVector = BrazierActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
						VectorA = BrazierActor->GetActorLocation();
						DistanceA = DistacnceVector.Size();
					
						bDistanceASet = true;
					}
				}
			}
			else if(Actor->IsA(ATorchActor::StaticClass()))
			{
				//UE_LOG(LogTemp,Warning,TEXT("Found Torch"));
				ATorchActor* TorchActor = Cast<ATorchActor>(Actor);
				if(TorchActor == nullptr) return;
				if(OwnerComp.GetAIOwner()->LineOfSightTo(TorchActor))
				{
					if(TorchActor->bTorchLit)
					{
						//UE_LOG(LogTemp,Warning,TEXT("Can see Lit Torch"));
						DistacnceVector = TorchActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
						VectorA = TorchActor->GetActorLocation();
						DistanceA = DistacnceVector.Size();
						bDistanceASet = true;
					}
				}		
			}
			else if(Actor->IsA(AMainCharacter::StaticClass()))
			{
				//UE_LOG(LogTemp,Warning,TEXT("Sees Actor"));
				AMainCharacter* MainCharacter = Cast<AMainCharacter>(Actor);
				if(MainCharacter->bHoldingTorch)
				{
					UE_LOG(LogTemp,Warning,TEXT("Kim holds a torch"));
					if(MainCharacter->bTorchLit)
					{
						UE_LOG(LogTemp,Warning,TEXT("Torch is lit"));
						DistacnceVector = MainCharacter->GetActorLocation() - OwnerCharacter->GetActorLocation();
						VectorA = MainCharacter->GetActorLocation();
						DistanceA = DistacnceVector.Size();
						//UE_LOG(LogTemp,Warning,TEXT("2. Distance A = %f\tDistance B = %f"), DistanceA, DistanceB);
						bDistanceASet = true;
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
						UE_LOG(LogTemp,Warning,TEXT("Torch is lit"));
						DistacnceVector = TorchHolderActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
						VectorA = TorchHolderActor->GetActorLocation();
						DistanceA = DistacnceVector.Size();
						//UE_LOG(LogTemp,Warning,TEXT("2. Distance A = %f\tDistance B = %f"), DistanceA, DistanceB);
						bDistanceASet = true;
					}
				}
			}
			if(bDistanceASet && DistanceA < DistanceB)
			{
				DistanceB = DistanceA;
				VectorB = VectorA;
				//UE_LOG(LogTemp,Warning,TEXT("3. Distance A = %f\tDistance B = %f"), DistanceA, DistanceB);
			}
			bDistanceASet = false;
		}
	}
	if(VectorB == FVector(0.f))
	{
		//UE_LOG(LogTemp,Warning,TEXT("Clears Value"));
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
	else
	{
		//UE_LOG(LogTemp,Warning,TEXT("Sets Value"));
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), VectorB);
	}
	//UE_LOG(LogTemp,Warning,TEXT("Update Location FireLoc done"));
}

