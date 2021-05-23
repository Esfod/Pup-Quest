// Fill out your copyright notice in the Description page of Project Settings.


#include "PlankActor.h"

APlankActor::APlankActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;
}
