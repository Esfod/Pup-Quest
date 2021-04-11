// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoorActor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "PupQuest/Characters/MainCharacter.h"
#include "PupQuest/Actors/TorchHolderActor.h"

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

	if(!bTorchHolder)
	{
		UE_LOG(LogTemp,Warning,TEXT("Haven't implemented pressurePlate yet"));
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

	if(TypeOfDoor == 1)
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
	if (a->bHasATorch) return true;
	return false;
}

bool ABaseDoorActor::CheckTorchHolder(ATorchHolderActor* a, ATorchHolderActor* b)
{
	if(a->bHasATorch && b->bHasATorch)
		return true;
	return false;
}

void ABaseDoorActor::OpenDoor(float DeltaTime)
{
	//add universale lyder og effekter
}
