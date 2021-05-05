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
		UE_LOG(LogTemp,Warning,TEXT("åpne"));
		if(Current==Initial)
		{
			UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation());
		}
		Current = FMath::Lerp(Current, MoveLength, DeltaTime * DoorOpenSpeed); //Open Door
		if(MoveLength > 0.f && Current+1 >= MoveLength+Initial) Current = MoveLength;//|| MoveLength < 0.f && Current <= MoveLength+1
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Lukke"));
		if(Current==MoveLength)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CloseDoorSound, GetActorLocation());
		}
		Current = FMath::Lerp(Current, Initial, DeltaTime * DoorCloseSpeed); //Open Door
		if(MoveLength > 0.f && Current-1 <= Initial) Current = Initial; //|| MoveLength < 0.f && Current <= Initial+1
	}
	
	FRotator DoorRotator = GetActorRotation();
	DoorRotator.Yaw = Current;
	SetActorRotation(DoorRotator);

}

