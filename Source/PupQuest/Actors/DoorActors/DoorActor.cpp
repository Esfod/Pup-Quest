// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"

ADoorActor::ADoorActor()
{
}

void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	Initial = GetActorRotation().Yaw;
	Current = Initial;
	MoveLength += Initial;
}


void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	bOpenDoor = CheckTorchHolder();

	OpenDoor(DeltaTime);
}

void ADoorActor::OpenDoor(float DeltaTime)
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
	DoorRotation.Yaw = Current;
	SetActorRotation(DoorRotation);
}
