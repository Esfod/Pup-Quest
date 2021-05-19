// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate_Actor.h"

#include "ItemsActor/BarrelActor.h"


APressurePlate_Actor::APressurePlate_Actor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComp;
}

ABarrelActor* APressurePlate_Actor::GetBarrelActor() const
{
	return BarrelActor; //returns the reference to the barrel that's on the pressureplate
}

void APressurePlate_Actor::PlaceBarrelRight(ABarrelActor* a)
{
	BarrelActor = a; //saves the barrel that comes from the parameter

	BarrelActor->SetActorRotation(FRotator(0.f,90.f,-90.f)); //put it at a fixed rotation and a fixed rotation 
	BarrelActor->SetActorLocation(GetActorLocation() + FVector(45.f,0.f, 85.f));
}

