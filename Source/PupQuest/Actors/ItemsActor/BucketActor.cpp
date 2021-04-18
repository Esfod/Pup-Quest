// Fill out your copyright notice in the Description page of Project Settings.


#include "BucketActor.h"

ABucketActor::ABucketActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	Water = CreateDefaultSubobject<UStaticMeshComponent>("Water");
	Water->SetupAttachment(MeshComp);

}

void ABucketActor::BeginPlay()
{
	if (bBucketFilled == false) {
		BucketWithoutWater();
	}
	else if (bBucketFilled == true) {
		BucketWithWater();
	}
}

void ABucketActor::BucketWithWater() {
	Water->SetVisibility(true);
	bBucketFilled = true;
}

void ABucketActor::BucketWithoutWater() {
	Water->SetVisibility(false);
	bBucketFilled = false;
}