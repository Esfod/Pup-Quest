// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateClosestFireDist.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTService_UpdateClosestFireDist : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_UpdateClosestFireDist();
protected:
	UPROPERTY(EditAnywhere, Category=Blackboard)
	struct FBlackboardKeySelector FireLocation;
private:
	float Distance {0.f};
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
