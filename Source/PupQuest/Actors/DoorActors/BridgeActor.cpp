// Written by 3016


#include "BridgeActor.h"

ABridgeActor::ABridgeActor()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void ABridgeActor::BeginPlay()
{
	Super::BeginPlay();

	Initial = GetActorRotation().Roll;	//get's the start value of the bridge
	Current = Initial;					//set's the current value equal to start value
	TotalMoveLength += Initial;			//sets the distance to move to equal. to the Length to move + start value
}

void ABridgeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	OpenDoor(DeltaTime); //open door
}

void ABridgeActor::OpenDoor(float DeltaTime)
{
	Super::OpenDoor(DeltaTime);
	if(bOpenDoor && !CloseDoorOverride) //checks of the door is suppose to open. and the override is false
	{
		if(!IsDoorOpen)//if it just came from that the bridge was closing ("else")
		{
			UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation()); //plays open door sound
			IsDoorOpen = true; //sets that the door is opening, so it dose not repeat opening sound
		}
		Current = FMath::Lerp(Current, TotalMoveLength, DeltaTime * DoorOpenSpeed); //gets a value between current and the location to move to //this makes the animation smooth
	}
	else //Close door
	{
		if(IsDoorOpen)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CloseDoorSound, GetActorLocation()); //plays close bridge sound
			IsDoorOpen = false;
		}
		Current = FMath::Lerp(Current, Initial, DeltaTime * DoorCloseSpeed); //Close Door
	}
	FRotator DoorRotator = GetActorRotation();	//gets the door rotator
	DoorRotator.Roll = Current;					//updates the door rotation's roll to the new current value
	SetActorRotation(DoorRotator);				//puts the new rotator in the to the bride
}