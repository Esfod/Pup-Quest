// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DistanceToAttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTService_DistanceToAttackPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_DistanceToAttackPlayer();
private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
