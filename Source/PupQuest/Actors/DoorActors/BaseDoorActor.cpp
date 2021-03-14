// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoorActor.h"
#include "PupQuest/Actors/ItemsActor/BaseItemActor.h"
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
	
}

bool ABaseDoorActor::CheckTorchHolder()
{
	TArray<AActor*> OverlappingActors;
	
	if(TorchHolder)
	{
		TorchHolder->GetOverlappingActors(OverlappingActors);
		for(AActor* Actor : OverlappingActors)
		{
			UE_LOG(LogTemp,Warning,TEXT("%s"), *Actor->GetName());

			if(Actor->IsA(AMainCharacter::StaticClass()))//Debug uses Player to test
			{
				return true;
			}
		}
	}
	
	return false;
}

void ABaseDoorActor::OpenDoor(float DeltaTime)
{
	//add universale lyder og effekter
}
