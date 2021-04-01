// Fill out your copyright notice in the Description page of Project Settings.


#include "TorchActor.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystem.h"


ATorchActor::ATorchActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	LightSorce = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	LightSorce->SetupAttachment(MeshComp);

	Flame = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlameParticle"));
	Flame->SetupAttachment(MeshComp);
}

void ATorchActor::BeginPlay()
{
	Super::BeginPlay();

	if (bTorchLit == false) {
		TorchFlameOff();
	}
	else {
		TorchFlameOn();
	}

}

void ATorchActor::TorchFlameOn() {
	Flame->SetVisibility(true);
	LightSorce->SetVisibility(true);
}

void ATorchActor::TorchFlameOff() {
	Flame->SetVisibility(false);
	LightSorce->SetVisibility(false);
}