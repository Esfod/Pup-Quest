// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDoorActor.h"
#include "BridgeActor.generated.h"

/**
 * 
 */
UCLASS()
class PUPQUEST_API ABridgeActor : public ABaseDoorActor
{
	GENERATED_BODY()

public:
	ABridgeActor();
protected:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OpenDoor(float DeltaTime) override;
};
