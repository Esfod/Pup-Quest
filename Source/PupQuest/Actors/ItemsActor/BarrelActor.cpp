// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrelActor.h"
#include "Kismet/GameplayStatics.h"
#include "PupQuest/Actors/PressurePlate_Actor.h"
#include "PupQuest/Characters/MainCharacter.h"
#include "DrawDebugHelpers.h"


// Sets default values
ABarrelActor::ABarrelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	Water = CreateDefaultSubobject<UStaticMeshComponent>("Water");
	Water->SetupAttachment(MeshComp);
}


void ABarrelActor::CheckIfOnPressurePlate()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> ActorsToIgnore;
	DrawDebugBox(GetWorld(),GetActorLocation() + FVector(-50.f,0.f,-50) , FVector(100.f,50.f,20.f), FColor::Red, true,2);
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), GetActorLocation() + FVector(-50.f,0.f,-50) , FVector(100.f,50.f,20.f), ObjectTypes, nullptr, ActorsToIgnore, OverlappedActors);
	for (AActor* Actor : OverlappedActors)
	{
		if(Actor->IsA(APressurePlate_Actor::StaticClass()))
		{
			APressurePlate_Actor* PressurePlate = Cast<APressurePlate_Actor>(Actor);
			PressurePlate->PlaceBarrelRight(this);
			return;
		}
	}
}

// Called when the game starts or when spawned
void ABarrelActor::BeginPlay()
{
	Super::BeginPlay();
	if (bBarrelFilled == false) {
		BarrelEmpty();
	}
	else if (bBarrelFilled == true) {
		bBarrelFilled = true;
		Water->SetVisibility(true);
		//The reason this is separated from the function is because we dont want to hear the barrel fill sound when we start the game
	}
}

// Called every frame
void ABarrelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABarrelActor::BarrelFill()
{
	Water->SetVisibility(true);
	bBarrelFilled = true;
	UGameplayStatics::PlaySoundAtLocation(this, FillBarrel, GetActorLocation());
}

void ABarrelActor::BarrelEmpty() {
	Water->SetVisibility(false);
	bBarrelFilled = false;
}



//void ABarrelActor::FindClosestPush()
//{
//}
//
//void ABarrelActor::HandleInteraction()
//{
//}
