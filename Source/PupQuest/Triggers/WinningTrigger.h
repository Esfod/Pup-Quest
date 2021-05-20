// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "WinningTrigger.generated.h"


UCLASS()
class PUPQUEST_API AWinningTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	AWinningTrigger();

	UFUNCTION()
		void OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere, Category = "Next Level")
		FName RestartLevel;
};
