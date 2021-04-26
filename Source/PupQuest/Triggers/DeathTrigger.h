// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DeathTrigger.generated.h"


UCLASS()
class PUPQUEST_API ADeathTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ADeathTrigger();

	UFUNCTION()
		void OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor);
};
