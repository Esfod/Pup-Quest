// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SoundTrigger.generated.h"

UCLASS()
class PUPQUEST_API ASoundTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ASoundTrigger();

	UFUNCTION()
		void OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere, Category = "Sound Effect")
		USoundBase* SoundEffect;

	bool bSoundPlayed = false;
};
