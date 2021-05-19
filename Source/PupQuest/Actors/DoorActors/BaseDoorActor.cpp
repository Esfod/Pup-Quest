// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoorActor.h"

#include "PupQuest/Actors/PressurePlate_Actor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "PupQuest/Actors/TorchHolderActor.h"
#include "PupQuest/Actors/ItemsActor/BarrelActor.h"

// Sets default values
ABaseDoorActor::ABaseDoorActor()
{
	PrimaryActorTick.bCanEverTick = true; 

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeh Component"));
	RootComponent = StaticMeshComp;
}

void ABaseDoorActor::BeginPlay()
{
	Super::BeginPlay();

	//checks what the door opening mechanism is
	if(!bTorchHolder && PressurePlate_Actor) 
	{
		UE_LOG(LogTemp,Warning,TEXT("One pressurePlate yet"));
		TypeOfDoor = 0; //gives the door a type
	}
	else if (TorchHolder1 && TorchHolder2)
	{
		UE_LOG(LogTemp,Warning,TEXT("two torches"));
		TypeOfDoor = 1;
	}
	else if (TorchHolder1)
	{
		UE_LOG(LogTemp,Warning,TEXT("one torch"));
		TypeOfDoor = 2;
	}
}

void ABaseDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(TypeOfDoor == 0)
	{
		bOpenDoor = CheckPressurePlate(PressurePlate_Actor); //checks if the pressureplate has meet requirement to open the door
	}
	else if(TypeOfDoor == 1)
	{
		bOpenDoor = CheckTorchHolder(TorchHolder1, TorchHolder2); //checks if the torchholder's has meet requirement to open the door
	}
	else if (TypeOfDoor == 2)
	{
		bOpenDoor = CheckTorchHolder(TorchHolder1);	
	}
}

bool ABaseDoorActor::CheckTorchHolder(ATorchHolderActor* a)
{
	if (a->HasATorch()) return true; //checks if it has a torch, doesn't need to check if it's lit because the player not able to place torch that's not lit
	return false; 
}

bool ABaseDoorActor::CheckTorchHolder(ATorchHolderActor* a, ATorchHolderActor* b)
{
	if(a->HasATorch() && b->HasATorch()) //checks both 
		return true;
	return false;
}

bool ABaseDoorActor::CheckPressurePlate(APressurePlate_Actor* a)
{

	if(!a->GetBarrelActor()) return false; //checks for nullptr

	if(a->GetBarrelActor()->bBarrelFilled)//checks if barrel if full
		return true;



	return false;
}

void ABaseDoorActor::OpenDoor(float DeltaTime)
{
	//add universale lyder og effekter
}

void ABaseDoorActor::CloseDoor()
{
	CloseDoorOverride = true;
}