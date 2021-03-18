// Fill out your copyright notice in the Description page of Project Settings.


#include "BrazierActor.h"

// Sets default values
ABrazierActor::ABrazierActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ABrazierActor::BeginPlay()
{
	Super::BeginPlay();
	
}



