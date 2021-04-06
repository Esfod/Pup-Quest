// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderWebActor.h"
#include "BrazierActor.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "BrazierActor.h"



// Sets default values
ASpiderWebActor::ASpiderWebActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBoxWeb = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxWeb"));
	HitBoxWeb->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	HitBoxWeb->SetupAttachment(RootComponent);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	LightSorce = CreateDefaultSubobject<UPointLightComponent>("PointLight");
	LightSorce->SetupAttachment(MeshComp);

	Flame = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FlameParticle"));
	Flame->SetupAttachment(MeshComp);

	

	HitBoxWeb->OnComponentBeginOverlap.AddDynamic(this, &ASpiderWebActor::BeginOverlapWeb);

}

// Called when the game starts or when spawned
void ASpiderWebActor::BeginPlay()
{
	Super::BeginPlay();
	Flame->SetVisibility(false);
	LightSorce->SetVisibility(false);
	//HitBoxWeb->SetGenerateOverlapEvents(false);

	
}

// Called every frame
void ASpiderWebActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Red, true, -1, 0, 5);


	//SetActorScale3D(FVector(Scale));//Krymper Web

	//while (burning == true) {
	//	Scale -= FVector(0.001f);
	//}
	//AddActorLocalTransform(FTransform(FVector(-0.1f)));
	//SetActorScale3D

}
void ASpiderWebActor::StartBurnWeb() {
	bBurning = true;
	SetActorScale3D(FVector(0.15));//Krymper Web
	HitBoxWeb->SetRelativeScale3D(FVector(24.f));//Når Web krymper krymper også Hitbox, så Hitbox må bli større igjen for å fange opp 

	UE_LOG(LogTemp, Warning, TEXT("Burn web"));

	Flame->SetVisibility(true);
	LightSorce->SetVisibility(true);

	GetWorld()->GetTimerManager().SetTimer(TimeGone, this, &ASpiderWebActor::EndBurnWeb, 1.f, false);
}

void ASpiderWebActor::EndBurnWeb() {
	SetActorHiddenInGame(true);
	//HitBoxWeb->SetGenerateOverlapEvents(true);
	HitBoxWeb->SetRelativeLocation(HitBoxWeb->GetRelativeLocation() + 1.f);
	SetActorEnableCollision(false);

	UE_LOG(LogTemp, Warning, TEXT("Test"));


	//HitBoxWeb->SetGenerateOverlapEvents(false);
	HitBoxWeb->SetRelativeLocation(HitBoxWeb->GetRelativeLocation() - 1.f);

	Flame->SetVisibility(false);
	LightSorce->SetVisibility(false);
	//burning = false;
}


void ASpiderWebActor::BeginOverlapWeb(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Web detects %s"), *OtherActor->GetName());
		if (OtherActor->IsA(ASpiderWebActor::StaticClass()) && OtherActor != this) {
		ASpiderWebActor* SpiderWeb = Cast<ASpiderWebActor>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Web detects %s"), *OtherActor->GetName());

			if (SpiderWeb->bBurning == false) {
			SpiderWeb->StartBurnWeb();
			}
		}

		if (OtherActor->IsA(ABrazierActor::StaticClass()) && OtherActor != this) {
			ABrazierActor* Brazier = Cast<ABrazierActor>(OtherActor);
			UE_LOG(LogTemp, Warning, TEXT("Web detects %s"), *OtherActor->GetName());

				StartBurnWeb();
			
		}
}


