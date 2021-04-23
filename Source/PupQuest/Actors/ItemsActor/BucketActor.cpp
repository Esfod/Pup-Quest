// Fill out your copyright notice in the Description page of Project Settings.


#include "BucketActor.h"
#include "Kismet/GameplayStatics.h"

ABucketActor::ABucketActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	Water = CreateDefaultSubobject<UStaticMeshComponent>("Water");
	Water->SetupAttachment(MeshComp);

}

void ABucketActor::BeginPlay()
{
	//These are so that when you start the game, the game will be in the right state based on if you ticked bucket filled or not in the details in the editor
	if (bBucketFilled == false) {
		BucketEmpty();
	}
	else if (bBucketFilled == true) {
		Water->SetVisibility(true);
		bBucketFilled = true;
		//The reason this is separated from the function is because we dont want to hear the bucket fill when we start the game
	}
}

void ABucketActor::BucketFill() {
	Water->SetVisibility(true);
	bBucketFilled = true;
	UGameplayStatics::PlaySoundAtLocation(this, FillBucket, GetActorLocation());
}

void ABucketActor::BucketEmpty() {
	Water->SetVisibility(false);
	bBucketFilled = false;
}