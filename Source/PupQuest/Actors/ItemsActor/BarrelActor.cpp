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
//=====3016=====
void ABarrelActor::CheckIfOnPressurePlate() // runs when the player is done with pushing the barrel, This is called from Blueprint
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> ActorsToIgnore;
	//DrawDebugBox(GetWorld(),GetActorLocation() + FVector(0.f,0,-120.f) , FVector(50.f), FColor::Red, true,2);
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), GetActorLocation() + FVector(0.f,0,-120.f) , FVector(50.f), ObjectTypes, nullptr, ActorsToIgnore, OverlappedActors);
	//collects the all actors that's under the barrel
	for (AActor* Actor : OverlappedActors) //goes trough all actors
		{
		if(Actor->IsA(APressurePlate_Actor::StaticClass())) //stops if it comes over an pressureplate
			{
			APressurePlate_Actor* PressurePlate = Cast<APressurePlate_Actor>(Actor); //cast's it to gain the public variables and function of the pressureplate
			PressurePlate->PlaceBarrelRight(this);
			IsLaying = false;
			return;
			}
		}
}

void ABarrelActor::RotateBarrel() //called when the player interacts with an laying barrel
{
	SetActorRotation(GetActorRotation()+FRotator(0.f,90.f,0.f)); //roates the barrel 90 degrees,  
}
//=====3016=====
//void ABarrelActor::FindClosestPush()
//{
//}
//
//void ABarrelActor::HandleInteraction()
//{
//}
