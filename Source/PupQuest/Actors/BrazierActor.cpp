// Fill out your copyright notice in the Description page of Project Settings.


#include "BrazierActor.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystem.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
ABrazierActor::ABrazierActor()
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	MeshComp->SetRelativeScale3D(FVector(10.f));
	RootComponent = MeshComp;

	BrazierLightSource = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	BrazierLightSource->SetupAttachment(MeshComp);

	BrazierFlame = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlameParticle"));
	BrazierFlame->SetupAttachment(MeshComp);
	
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
	bBrazierLit = true;

	BrazierFlame->SetVisibility(true);
	BrazierLightSource->SetVisibility(true);
	UGameplayStatics::PlaySoundAtLocation(this, BurningSound, GetActorLocation() - FVector(624.f, 625.f, -884.f));//The added FVector is a temporary solution, the sound gets picked up by the camera instead of the player, so I added the distance between the player and the camera to where the sound will play

}

void ABrazierActor::BrazierFlameOff() {
	BrazierFlame->SetVisibility(false);
	BrazierLightSource->SetVisibility(false);
	bBrazierLit = false;
}





