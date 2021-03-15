// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDoorActor.h"
#include "DoorActor.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API ADoorActor : public ABaseDoorActor
{
	GENERATED_BODY()
protected:
	ADoorActor();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OpenDoor(float DeltaTime) override;
};