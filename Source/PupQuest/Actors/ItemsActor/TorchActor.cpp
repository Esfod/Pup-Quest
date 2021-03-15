// Fill out your copyright notice in the Description page of Project Settings.


#include "TorchActor.h"
#include "Components/SkeletalMeshComponent.h"

ATorchActor::ATorchActor()
{
MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
RootComponent = MeshComp;

}

void ATorchActor::BeginPlay()
{
	Super::BeginPlay();

}