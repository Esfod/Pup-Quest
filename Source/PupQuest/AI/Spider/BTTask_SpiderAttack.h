// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SpiderAttack.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTTask_SpiderAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SpiderAttack(); 
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
};
