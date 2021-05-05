// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate_Actor.h"

#include "ItemsActor/BarrelActor.h"


APressurePlate_Actor::APressurePlate_Actor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComp;
}


void APressurePlate_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}


void APressurePlate_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ABarrelActor* APressurePlate_Actor::GetBarrelActor() const
{
	return BarrelActor;
}

void APressurePlate_Actor::PlaceBarrelRight(ABarrelActor* a)
{
	BarrelActor = a;

	BarrelActor->SetActorRotation(FRotator(0.f,-90.f,-90.f));
	BarrelActor->SetActorLocation(GetActorLocation() + FVector(-65.f,0.f, 85.f));
}

