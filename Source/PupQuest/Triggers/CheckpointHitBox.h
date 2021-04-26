// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CheckpointHitBox.generated.h"

UCLASS()
class PUPQUEST_API ACheckpointHitBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ACheckpointHitBox();

	UFUNCTION()
		void OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor);
	
	UPROPERTY(EditAnywhere, Category = "NewSpawn")
		FVector Location;

};
