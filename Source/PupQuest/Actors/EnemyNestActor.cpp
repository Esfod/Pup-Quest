// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyNestActor.h"

// Sets default values
AEnemyNestActor::AEnemyNestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Nest Mesh");
	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void AEnemyNestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyNestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

