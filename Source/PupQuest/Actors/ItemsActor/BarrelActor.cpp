// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrelActor.h"

// Sets default values
ABarrelActor::ABarrelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ABarrelActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarrelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrelActor::FindClosestPush()
{
}

void ABarrelActor::HandleInteraction()
{
}
