// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CloseDoorTriggerBox.generated.h"

class ABaseDoorActor;
UCLASS()
class PUPQUEST_API ACloseDoorTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
	public:
	ACloseDoorTriggerBox();
	UFUNCTION()
		void OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor);
	protected:
	UPROPERTY(EditAnywhere,Category=Doors)
		ABaseDoorActor* DoorToClose {nullptr};
};
