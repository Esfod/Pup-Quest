// Written by 3016

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindClosestNestLoc.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTService_FindClosestNestLoc : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	public:
	UBTService_FindClosestNestLoc(); 
	private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
