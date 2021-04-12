// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RunAwayFromFire.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTTask_RunAwayFromFire : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_RunAwayFromFire();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, Category=Blackboard)
	struct FBlackboardKeySelector BlackboardKey; 
};
