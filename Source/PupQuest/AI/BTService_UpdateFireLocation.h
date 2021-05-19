// Written by 3016

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateFireLocation.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API UBTService_UpdateFireLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_UpdateFireLocation(); 
private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
