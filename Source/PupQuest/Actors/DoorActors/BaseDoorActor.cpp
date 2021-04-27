// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoorActor.h"

#include "PupQuest/Actors/PressurePlate_Actor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "PupQuest/Characters/MainCharacter.h"
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

	if(!bTorchHolder && PressurePlate_Actor)
	{
		UE_LOG(LogTemp,Warning,TEXT("One pressurePlate yet"));
		TypeOfDoor = 0;
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
		bOpenDoor = CheckPressurePlate(PressurePlate_Actor);
	}
	else if(TypeOfDoor == 1)
	{
		bOpenDoor = CheckTorchHolder(TorchHolder1, TorchHolder2);
	}
	else if (TypeOfDoor == 2)
	{
		bOpenDoor = CheckTorchHolder(TorchHolder1);	
	}
}

bool ABaseDoorActor::CheckTorchHolder(ATorchHolderActor* a)
{
	if (a->HasATorch()) return true;
	return false; 
}

bool ABaseDoorActor::CheckTorchHolder(ATorchHolderActor* a, ATorchHolderActor* b)
{
	if(a->HasATorch() && b->HasATorch())
		return true;
	return false;
}

bool ABaseDoorActor::CheckPressurePlate(APressurePlate_Actor* a)
{

	if(!a->GetBarrelActor()) return false;

	if(a->GetBarrelActor()->bBarrelFilled)
		return true;

	return false;
}

void ABaseDoorActor::OpenDoor(float DeltaTime)
{
	//add universale lyder og effekter
}
