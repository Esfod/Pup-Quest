// Written by 3016

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
	float DistanceBetween {0.f};
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
