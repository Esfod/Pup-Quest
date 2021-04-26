// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_AntAttack.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTTaskNode_AntAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_AntAttack();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;	

};
