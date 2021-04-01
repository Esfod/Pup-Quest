// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attac.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTTask_Attac : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Attac();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	
};
