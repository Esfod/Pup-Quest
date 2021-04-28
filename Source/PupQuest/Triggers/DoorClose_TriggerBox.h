// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DoorClose_TriggerBox.generated.h"


class ABaseDoorActor;

UCLASS()
class PUPQUEST_API ADoorClose_TriggerBox : public ATriggerBox
{
	GENERATED_BODY()
public:
    ADoorClose_TriggerBox();
    
    UFUNCTION()
    	void OnOverlap(class AActor* OverlappedActor, class AActor* OtherActor);
private:

    UPROPERTY(EditAnywhere, Category = "Next Level",meta = (AllowPrivateAccess = "true"))
    	ABaseDoorActor* DoorToClose;
};
