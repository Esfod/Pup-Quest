// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderWeb.h"

// Sets default values
ASpiderWeb::ASpiderWeb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ASpiderWeb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpiderWeb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

