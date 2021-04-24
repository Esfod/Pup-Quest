// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Ant.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API AAIController_Ant : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override; 

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior{nullptr};
};
