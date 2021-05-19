// Written by 3016

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_IsplayerHoldingTorch.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTService_IsplayerHoldingTorch : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_IsplayerHoldingTorch();
	
	UPROPERTY(EditAnywhere, Category=Blackboard)
	struct FBlackboardKeySelector BlackboardKey;
private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
