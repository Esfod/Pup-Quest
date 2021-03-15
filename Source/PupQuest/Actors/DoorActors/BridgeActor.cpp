// Fill out your copyright notice in the Description page of Project Settings.


#include "BridgeActor.h"

ABridgeActor::ABridgeActor()
{
}

void ABridgeActor::BeginPlay()
{
	Super::BeginPlay();
	
	Initial = GetActorRotation().Pitch;
	Current = Initial;
	MoveLength += Initial;
}

void ABridgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	bOpenDoor = CheckTorchHolder();

	OpenDoor(DeltaTime);
}

void ABridgeActor::OpenDoor(float DeltaTime)
{
	Super::OpenDoor(DeltaTime);

	if(bOpenDoor)
	{
		Current = FMath::Lerp(Current, MoveLength, DeltaTime * DoorOpenSpeed); //Open Door
	}
	else
	{
		Current = FMath::Lerp(Current, Initial, DeltaTime * DoorCloseSpeed); //Open Door
	}
	FRotator DoorRotation = GetActorRotation();
	DoorRotation.Pitch = Current;
	SetActorRotation(DoorRotation);
}