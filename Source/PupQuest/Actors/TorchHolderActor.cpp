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

ATorchActor* ATorchHolderActor::GetTorchActor()
{
	return TorchActor;
}

bool ATorchHolderActor::HasATorch()
{
	return bHasATorch;
}

void ATorchHolderActor::SetTorchActor(ATorchActor* NewTorchActor)
{
	TorchActor = NewTorchActor;
	if(TorchActor)
		bHasATorch = true;
	else
		bHasATorch = false;
}

FTransform ATorchHolderActor::GetTorchPlacementPoint() 
{
	return TorchPlacementPoint->GetComponentTransform();
}
