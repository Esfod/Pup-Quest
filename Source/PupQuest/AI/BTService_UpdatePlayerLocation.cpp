// Written by 3016


#include "BTService_UpdatePlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTService_UpdatePlayerLocation::UBTService_UpdatePlayerLocation()
{
	NodeName = TEXT("Update Player Location");
}

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if(PlayerPawn == nullptr) return;
	
	if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),PlayerPawn->GetActorLocation());
	}
	else
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
}
