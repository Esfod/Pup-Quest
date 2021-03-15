// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderWebActor.h"

// Sets default values
ASpiderWebActor::ASpiderWebActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASpiderWebActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpiderWebActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

