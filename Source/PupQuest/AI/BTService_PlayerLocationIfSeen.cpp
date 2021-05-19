// Written by 3016


#include "BTService_PlayerLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Spider/AIController_Spider.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Update Player Location If seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); 
	
	if(PlayerPawn == nullptr || OwnerComp.GetAIOwner() == nullptr) return;
	
	if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn)) //Checks if the enemy has Line Of Sight To the main character
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),PlayerPawn->GetActorLocation()); //updates the value of the location of the main character
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); //clears value of the location of the main character
	}
}