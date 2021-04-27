// Fill out your copyright notice in the Description page of Project Settings.


#include "SecretChestActor.h"

// Sets default values
ASecretChestActor::ASecretChestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestBottom = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = ChestBottom;

	ChestTop = CreateDefaultSubobject<UStaticMeshComponent>("PointLight");
	ChestTop->SetupAttachment(ChestBottom);
}

// Called when the game starts or when spawned
void ASecretChestActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASecretChestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

