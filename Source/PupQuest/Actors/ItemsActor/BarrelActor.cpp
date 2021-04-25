// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrelActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABarrelActor::ABarrelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	Water = CreateDefaultSubobject<UStaticMeshComponent>("Water");
	Water->SetupAttachment(MeshComp);
}




// Called when the game starts or when spawned
void ABarrelActor::BeginPlay()
{
	Super::BeginPlay();
	if (bBarrelFilled == false) {
		BarrelEmpty();
	}
	else if (bBarrelFilled == true) {
		bBarrelFilled = true;
		Water->SetVisibility(true);
		//The reason this is separated from the function is because we dont want to hear the barrel fill sound when we start the game
	}
}

// Called every frame
void ABarrelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABarrelActor::BarrelFill() {
	Water->SetVisibility(true);
	bBarrelFilled = true;
	UGameplayStatics::PlaySoundAtLocation(this, FillBarrel, GetActorLocation());
}

void ABarrelActor::BarrelEmpty() {
	Water->SetVisibility(false);
	bBarrelFilled = false;
}



//void ABarrelActor::FindClosestPush()
//{
//}
//
//void ABarrelActor::HandleInteraction()
//{
//}
