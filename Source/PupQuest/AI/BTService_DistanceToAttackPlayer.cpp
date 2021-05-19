// Written by 3016


#include "BTService_DistanceToAttackPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_DistanceToAttackPlayer::UBTService_DistanceToAttackPlayer()
{
	NodeName = TEXT("Distance To Player");
}

void UBTService_DistanceToAttackPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* PlayerPawn = Cast<APawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if(OwnerPawn == nullptr || PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("UBTService_DistanceToAttackPlayer() Cast failed"));
		return;
	}

	if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)) //Checks if the enemy has Line Of Sight To the main character
	{
		DistanceBetween = FVector(OwnerPawn->GetActorLocation() - PlayerPawn->GetActorLocation()).Size(); //big vector math
        
        UE_LOG(LogTemp,Warning,TEXT("DistanceBetween = %f"),DistanceBetween);	
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), DistanceBetween); //return the distance to the player
	}
	else
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); //clears the value if the enemy dose not see the main character
}