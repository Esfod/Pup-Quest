// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDoorActor.h"
#include "GateActor.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API AGateActor : public ABaseDoorActor
{
	GENERATED_BODY()
	
protected:
	AGateActor();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OpenDoor(float DeltaTime) override;
};
