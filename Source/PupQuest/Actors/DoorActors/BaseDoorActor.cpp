// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDoorActor.h"
#include "PupQuest/Characters/MainCharacter.h"

// Sets default values
ABaseDoorActor::ABaseDoorActor()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	RootComponent = StaticMeshComp;
}

void ABaseDoorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseDoorActor::CheckTorchHolder()
{
	TArray<AActor*> OverlappingActors;
	if(TorchHolderActor)
	{
		TorchHolderActor->GetOverlappingActors(OverlappingActors);
		for(AActor* Actor : OverlappingActors)
		{
			UE_LOG(LogTemp,Warning,TEXT("%s"), *Actor->GetName());

			if(Actor->IsA(AMainCharacter::StaticClass()))
			{
				return true;
			}
		}
	}
	return false;
}

void ABaseDoorActor::OpenDoor(float DeltaTime)
{
	//adde universale lyder og effekter
}
