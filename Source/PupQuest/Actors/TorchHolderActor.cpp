// Fill out your copyright notice in the Description page of Project Settings.


#include "TorchHolderActor.h"

ATorchHolderActor::ATorchHolderActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeh Component"));
	RootComponent = StaticMeshComp;

	TorchPlacementPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Torch Placement Point"));
	TorchPlacementPoint->SetupAttachment(RootComponent);
}

void ATorchHolderActor::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ATorchHolderActor::GetTorchPlacementPoint() 
{
	return TorchPlacementPoint->GetComponentLocation();
}