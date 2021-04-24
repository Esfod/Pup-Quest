// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "PlacePlankTrigger.generated.h"

UCLASS()
class PUPQUEST_API APlacePlankTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	APlacePlankTrigger();

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere, Category = "Componets")
		FVector Location;

	UPROPERTY(EditAnywhere, Category = "Componets")
		FRotator Rotation;

};
