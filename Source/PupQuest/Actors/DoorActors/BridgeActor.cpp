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
	TotalMoveLength += Initial;
}

void ABridgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	
	OpenDoor(DeltaTime);
}

void ABridgeActor::OpenDoor(float DeltaTime)
{
	Super::OpenDoor(DeltaTime);
	if(bOpenDoor && !CloseDoorOverride)
	{
		if(!IsDoorOpen)
		{
			UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation());
			IsDoorOpen = true;
		}
		Current = FMath::Lerp(Current, TotalMoveLength, DeltaTime * DoorOpenSpeed); //Open Door
	}
	else
	{
		if(IsDoorOpen)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CloseDoorSound, GetActorLocation());
			IsDoorOpen = false;
		}
		Current = FMath::Lerp(Current, Initial, DeltaTime * DoorCloseSpeed); //Open Door
	}
	FRotator DoorRotator = GetActorRotation();
	DoorRotator.Roll = Current;
	SetActorRotation(DoorRotator);
}