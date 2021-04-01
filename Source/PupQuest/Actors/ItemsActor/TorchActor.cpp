// Fill out your copyright notice in the Description page of Project Settings.


#include "TorchActor.h"
#include "Components/PointLightComponent.h"

ATorchActor::ATorchActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	LightSorce = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	LightSorce->SetupAttachment(MeshComp);
}

void ATorchActor::BeginPlay()
{
	Super::BeginPlay();
}