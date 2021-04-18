// Fill out your copyright notice in the Description page of Project Settings.


#include "BridgeActor.h"

ABridgeActor::ABridgeActor()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void ABridgeActor::BeginPlay()
{
	Super::BeginPlay();

	Initial = GetActorRotation().Roll;
	Current = Initial;
	MoveLength += Initial;
}

void ABridgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	
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
	FRotator DoorRotator = GetActorRotation();
	DoorRotator.Roll = Current;
	SetActorRotation(DoorRotator);
}