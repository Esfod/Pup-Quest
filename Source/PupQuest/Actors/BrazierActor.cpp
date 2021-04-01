// Fill out your copyright notice in the Description page of Project Settings.


#include "BrazierActor.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystem.h"


// Sets default values
ABrazierActor::ABrazierActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	LightSorce = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	LightSorce->SetupAttachment(MeshComp);

	Flame = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlameParticle"));
	Flame->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void ABrazierActor::BeginPlay()
{
	Super::BeginPlay();

	if (bBrazierLit == false) {
		BrazierFlameOff();
	}
	else {
		BrazierFlameOn();
	}
	
}

void ABrazierActor::BrazierFlameOn() {
	Flame->SetVisibility(true);
	LightSorce->SetVisibility(true);
	bBrazierLit = true;
}

void ABrazierActor::BrazierFlameOff() {
	Flame->SetVisibility(false);
	LightSorce->SetVisibility(false);
	bBrazierLit = false;
}



