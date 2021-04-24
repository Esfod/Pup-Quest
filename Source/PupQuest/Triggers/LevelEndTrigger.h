// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LevelEndTrigger.generated.h"


UCLASS()
class PUPQUEST_API ALevelEndTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ALevelEndTrigger();

	UFUNCTION()
		void OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere, Category = "Next Level")
		FName NextLevel;
};
