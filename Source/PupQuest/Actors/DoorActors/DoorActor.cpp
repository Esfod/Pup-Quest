// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"

#include "Kismet/KismetSystemLibrary.h"

ADoorActor::ADoorActor()
{
	PrimaryActorTick.bCanEverTick = true;	
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
	
	OpenDoor(DeltaTime);
}

void ADoorActor::OpenDoor(float DeltaTime)
{
	Super::OpenDoor(DeltaTime);
	
	if(bOpenDoor && !CloseDoorOverride)
	{
		if(Current==MoveLength) return;
		//UE_LOG(LogTemp,Warning,TEXT("åpne"));
		if(Current==Initial) //playsound here

		Current = FMath::Lerp(Current, MoveLength, DeltaTime * DoorOpenSpeed); //Open Door
	}
	else
	{
		if(Current==Initial) return;
		//UE_LOG(LogTemp,Warning,TEXT("Lukke"));
		if(Current==MoveLength) //playsound here

		Current = FMath::Lerp(Current, Initial, DeltaTime * DoorCloseSpeed); //Open Door
	}
	FRotator DooRotator = GetActorRotation();
	DooRotator.Yaw = Current;
	SetActorRotation(DooRotator);
}

