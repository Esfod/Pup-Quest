// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CutSceneTrigger.generated.h"
//#include "MediaAssets/MediaPlayer.h"

UCLASS()
class PUPQUEST_API ACutSceneTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ACutSceneTrigger();

	UFUNCTION()
		void OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor);

	//Play video
	/*UPROPERTY(EditAnywhere, Category = "Sound Effect")
		USoundBase* SoundEffect;*/

	//UMediaPlayer* Test;

	bool bVideoPlayed = false;
};
