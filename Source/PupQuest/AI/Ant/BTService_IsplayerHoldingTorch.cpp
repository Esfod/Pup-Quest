// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsplayerHoldingTorch.h"

#include "PupQuest/Characters/MainCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"

UBTService_IsplayerHoldingTorch::UBTService_IsplayerHoldingTorch()
{
	NodeName = TEXT("Is MainCharacter Holding Torch");
}

void UBTService_IsplayerHoldingTorch::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0)); //cast's the main character

	if(MainCharacter== nullptr) //checks for nullptr
	{
		UE_LOG(LogTemp,Warning,TEXT("UBTService_IsplayerHoldingTorch fail cast Maincharacter"));
		OwnerComp.GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName); //clears the value
	}
	else if(MainCharacter->bHoldingTorch && MainCharacter->GetTorchActor()->bTorchActorLit) //checks if the player holds a lit torch
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackboardKey.SelectedKeyName, true); //returns a true to the blackboard
	}
	else
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackboardKey.SelectedKeyName, false); //returns a false to the blackboard

	
	
}
