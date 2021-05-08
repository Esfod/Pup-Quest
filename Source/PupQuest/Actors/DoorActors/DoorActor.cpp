// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "Kismet/GameplayStatics.h"


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
	TotalMoveLength += Initial;
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
		Current = FMath::Lerp(Current, Initial, DeltaTime * DoorCloseSpeed); //Close Door
	}
	
	FRotator DoorRotator = GetActorRotation();
	DoorRotator.Yaw = Current;
	SetActorRotation(DoorRotator);
}

