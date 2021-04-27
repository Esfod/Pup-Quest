// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate_Actor.h"

#include "ItemsActor/BarrelActor.h"


// Sets default values
APressurePlate_Actor::APressurePlate_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = StaticMeshComp;
}

// Called when the game starts or when spawned
void APressurePlate_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
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
	a->SetActorRotation(FRotator(0.f,180.f,0.f));
	a->SetActorLocation(GetActorLocation() + FVector(0.f,0.f,10.f));
}

