// Fill out your copyright notice in the Description page of Project Settings.


#include "GateActor.h"

AGateActor::AGateActor()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void AGateActor::BeginPlay()
{
	Super::BeginPlay();

	DoorOpenSpeed = 5.f;
	DoorCloseSpeed = 7.5;
	
	Initial = GetActorLocation().Z;
	Current = Initial;
	TotalMoveLength += Initial;
}

void AGateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	OpenDoor(DeltaTime);
}

void AGateActor::OpenDoor(float DeltaTime)
{
	Super::OpenDoor(DeltaTime);
	if(bOpenDoor)
	{
		Current = FMath::Lerp(Current, TotalMoveLength, DeltaTime * DoorOpenSpeed); //Open Door
	}
	else
	{
		Current = FMath::Lerp(Current, Initial, DeltaTime * DoorCloseSpeed); //Open Door
	}
	FVector DoorLocation = GetActorLocation();
	DoorLocation.Z = Current;
	SetActorLocation(DoorLocation);
}