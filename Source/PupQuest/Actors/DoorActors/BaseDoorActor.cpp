// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoorActor.h"
#include "PupQuest/Actors/ItemsActor/TorchActor.h"
#include "PupQuest/Characters/MainCharacter.h"

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

bool ABaseDoorActor::CheckTorchHolder(const AActor* a)
{
	TArray<AActor*> OverlappingActors;
	if(a)
	{
		a->GetOverlappingActors(OverlappingActors);
		for(AActor* Actor : OverlappingActors)
		{
			if(Actor->IsA(ATorchActor::StaticClass()) || Actor->IsA(AMainCharacter::StaticClass()))
			{
				UE_LOG(LogTemp,Warning,TEXT("åpne dør"));
				return true;
			}
		}
	}
	return false;
}

bool ABaseDoorActor::CheckTorchHolder(const AActor* a, const AActor* b)
{
	TArray<AActor*> OverlappingActors;
	UE_LOG(LogTemp,Warning,TEXT("hello from check torchholder 2"), );
	int x {0};
	a->GetOverlappingActors(OverlappingActors);
	for(AActor* Actor : OverlappingActors)
	{
		if(Actor->IsA(ATorchActor::StaticClass()))
		{
			UE_LOG(LogTemp,Warning,TEXT("Torch 1 er klar"));
			x++;
		}
	}

	b->GetOverlappingActors(OverlappingActors);
	for(AActor* Actor : OverlappingActors)
	{
		if(Actor->IsA(ATorchActor::StaticClass()))
		{
			UE_LOG(LogTemp,Warning,TEXT("Torch 2 er klar"));
			x++;
		}
	}
	if(x == 2)
		return true;
	
	return false;
}

void ABaseDoorActor::OpenDoor(float DeltaTime)
{
	//add universale lyder og effekter
}
