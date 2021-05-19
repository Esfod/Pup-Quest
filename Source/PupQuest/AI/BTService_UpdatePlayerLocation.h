// Written by 3016

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdatePlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTService_UpdatePlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_UpdatePlayerLocation(); 
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
