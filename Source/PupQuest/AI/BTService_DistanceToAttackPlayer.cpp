// Fill out your copyright notice in the Description page of Project Settings.


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
	if(PlayerPawn == nullptr) return;
	FVector VectorBetween = OwnerPawn-> GetActorLocation() - PlayerPawn->GetActorLocation();
	float DistanceBetween = VectorBetween.Size();
	UE_LOG(LogTemp,Warning,TEXT("DistanceBetween : %f"), DistanceBetween);
	
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), DistanceBetween);
}