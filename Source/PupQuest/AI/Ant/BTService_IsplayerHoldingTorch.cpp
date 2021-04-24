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
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	if(MainCharacter== nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("UBTService_IsplayerHoldingTorch fail cast Maincharacter"));
		OwnerComp.GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
	}
	else if(MainCharacter->bHoldingTorch && MainCharacter->GetTorchActor()->bTorchLit)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackboardKey.SelectedKeyName, true);
	}
	else
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(BlackboardKey.SelectedKeyName, false);

	
	
}
