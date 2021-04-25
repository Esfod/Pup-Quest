// Fill out your copyright notice in the Description page of Project Settings.


#include "TorchActor.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

ATorchActor::ATorchActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	LightSorce = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	LightSorce->SetupAttachment(MeshComp);

	Flame = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlameParticle"));
	Flame->SetupAttachment(MeshComp);
	//Flame->SetCollisionProfileName("NoCollision", false);
}

void ATorchActor::BeginPlay()
{
	Super::BeginPlay(); 

	if (bTorchActorLit == false) {
		TorchFlameOff();
	}
	else if (bTorchActorLit == true) {
		Flame->SetVisibility(true);
		LightSorce->SetVisibility(true);
		bTorchActorLit = true;
	}
}

void ATorchActor::TorchFlameOn() {
	Flame->SetVisibility(true);
	LightSorce->SetVisibility(true);
	bTorchActorLit = true;
	UGameplayStatics::PlaySoundAtLocation(this, LightTorchSound, GetActorLocation());
}

void ATorchActor::TorchFlameOff() {
	Flame->SetVisibility(false);
	LightSorce->SetVisibility(false);
	bTorchActorLit = false;
}