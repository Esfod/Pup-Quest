// Written by 3016

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Spider.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API AAIController_Spider : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override; 

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior{nullptr};
};
