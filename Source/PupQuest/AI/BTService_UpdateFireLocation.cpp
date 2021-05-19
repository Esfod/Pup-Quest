// Written by 3016


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
	TArray<AActor*> OverlappingActors = OwnerCharacter->GetOverLappingActorsFromSphere(); //runs the a function from enemy to get all actors in a radius of the player
	float DistanceA {0.f}; //an temporary variable
	float DistanceB {100000.f}; 
	FVector DistanceVector {0.f}; //an temporary variable
	FVector VectorA {0.f};
	FVector VectorB {0.f}; //the variable that will be returned to BehaviorTree outgoing 
	bool bDistanceASet {false};
	//UE_LOG(LogTemp,Warning,TEXT("1. Distance A = %f\tDistance B = %f"), DistanceA, DistanceB);

	for(AActor* Actor : OverlappingActors) //goes trough every actor
	{
		//UE_LOG(LogTemp,Warning,TEXT("%s"), *Actor->GetName());
		if(OwnerComp.GetAIOwner()->LineOfSightTo(Actor)) //checks if the enemy has lines of sight to the actor
		{
			if(Actor->IsA(ABrazierActor::StaticClass())) //checks if it's is' a brazier
			{
				ABrazierActor* BrazierActor = Cast<ABrazierActor>(Actor);
				if(BrazierActor->bBrazierLit) //checks if it's lit
				{
					//UE_LOG(LogTemp,Warning,TEXT("Can see lit Brazier"));
					DistanceVector = BrazierActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
					VectorA = BrazierActor->GetActorLocation();
					DistanceA = DistanceVector.Size();
					bDistanceASet = true;
					//calculates the distance to enemy and fire
				}
			}
			else if(Actor->IsA(ATorchActor::StaticClass())) //checks if it's is' a Torch
			{
				//UE_LOG(LogTemp,Warning,TEXT("Found Torch"));
				ATorchActor* TorchActor = Cast<ATorchActor>(Actor);
				if(TorchActor->bTorchActorLit)
				{
					//UE_LOG(LogTemp,Warning,TEXT("Can see Lit Torch"));
					DistanceVector = TorchActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
					VectorA = TorchActor->GetActorLocation();
					DistanceA = DistanceVector.Size();
					bDistanceASet = true;
					//calculates the distance to enemy and fire
				}
			}
			else if(Actor->IsA(AMainCharacter::StaticClass())) //checks if it's is' a main character
			{
				//UE_LOG(LogTemp,Warning,TEXT("Sees Actor"));
				AMainCharacter* MainCharacter = Cast<AMainCharacter>(Actor);
				if(MainCharacter)
				{
					if(MainCharacter->bHoldingTorch && MainCharacter->GetTorchActor()->bTorchActorLit) ////checks if it holds a torch and it's lit
					{
						//UE_LOG(LogTemp,Warning,TEXT("Kim holds a torch"));
						//UE_LOG(LogTemp,Warning,TEXT("Kim holdes a lit torch"));
						DistanceVector = MainCharacter->GetActorLocation() - OwnerCharacter->GetActorLocation();
						VectorA = MainCharacter->GetActorLocation();
						DistanceA = DistanceVector.Size();
						bDistanceASet = true;
						//calculates the distance to enemy and fire
					}
				}
			}
			else if(Actor->IsA(ATorchHolderActor::StaticClass()))
			{
				//UE_LOG(LogTemp,Warning,TEXT("hellllllooooooo I am an TorchHolder"));
				ATorchHolderActor* TorchHolderActor = Cast<ATorchHolderActor>(Actor);

				if(TorchHolderActor->HasATorch()) //checks if the torchholder holds a torch
				{
					//UE_LOG(LogTemp,Warning,TEXT("Can se torchholder with lit torch"));
					DistanceVector = TorchHolderActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
					VectorA = TorchHolderActor->GetActorLocation();
					DistanceA = DistanceVector.Size();
					bDistanceASet = true;
					//calculates the distance to enemy and fire
				}
			}
			
			if(bDistanceASet && DistanceA < DistanceB) //checks if goes trough something that's not a fire object, that the new distance is shorter than the new one
			{
				DistanceB = DistanceA; 
				VectorB = VectorA;
				//replaces the new variables with old ones
			}
			bDistanceASet = false; //resets the bool
		}
	}
	
	if(VectorB == FVector(0.f)) //checks if the new vector has been updated
	{
		//UE_LOG(LogTemp,Warning,TEXT("Clears Value"));
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); //clear's the value
	}
	else
	{
		//UE_LOG(LogTemp,Warning,TEXT("Sets Value"));
		//UE_LOG(LogTemp,Warning,TEXT("%s"), *VectorB.ToString());
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), VectorB); //return the closest fire location
	}
	//UE_LOG(LogTemp,Warning,TEXT("Update Location FireLoc done"));
}

