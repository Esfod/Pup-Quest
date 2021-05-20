// Written by 3016

#pragma once

#include "CoreMinimal.h"
#include "BaseDoorActor.h"
#include "BridgeActor.generated.h"

// when this is open it's laying
UCLASS()
class PUPQUEST_API ABridgeActor : public ABaseDoorActor
{
	GENERATED_BODY()
	
protected:
	ABridgeActor();
	
	virtual void BeginPlay() override; 

	virtual void Tick(float DeltaTime) override;

	virtual void OpenDoor(float DeltaTime) override;
};