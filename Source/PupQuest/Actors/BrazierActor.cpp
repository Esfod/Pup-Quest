// Fill out your copyright notice in the Description page of Project Settings.


#include "BrazierActor.h"
#include "SpiderWebActor.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"


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

	HitBoxBrazier = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxBrazier"));
	HitBoxBrazier->InitBoxExtent(FVector(50.f, 50.f, 50.f)); 
	HitBoxBrazier->SetupAttachment(RootComponent);

	HitBoxBrazier->OnComponentBeginOverlap.AddDynamic(this, &ABrazierActor::BeginOverlapBrazier);
	HitBoxBrazier->SetGenerateOverlapEvents(false);
	
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

void ABrazierActor::Tick(float DeltaTime) {

	//DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Red, true, -1, 0, 5);


}
void ABrazierActor::BrazierFlameOn() {
	bBrazierLit = true;

	BrazierFlame->SetVisibility(true);
	BrazierLightSource->SetVisibility(true);

	/*GetWorld()->GetTimerManager().SetTimer(TimeGone, this, &ABrazierActor::SearchForWeb, 1.f, false);*/
}

void ABrazierActor::BrazierFlameOff() {
	BrazierFlame->SetVisibility(false);
	BrazierLightSource->SetVisibility(false);
	bBrazierLit = false;
}

void ABrazierActor::SearchForWeb() {
	/*HitBoxBrazier->SetGenerateOverlapEvents(true);
	HitBoxBrazier->SetRelativeLocation(HitBoxBrazier->GetRelativeLocation() + 1.f);

	UE_LOG(LogTemp, Warning, TEXT("Brazier detects stuff"));*/
}

void ABrazierActor::BeginOverlapBrazier(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	//GetOverlappingActors();

	/*UE_LOG(LogTemp, Warning, TEXT("Brazier detects %s"), *OtherActor->GetName());

	if (OtherActor->IsA(ASpiderWebActor::StaticClass()) && OtherActor != this) {
		ASpiderWebActor* SpiderWeb = Cast<ASpiderWebActor>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Brazier1 detects %s"), *OtherActor->GetName());

		if (SpiderWeb->bBurning == false) {
			SpiderWeb->StartBurnWeb();
		}
	}*/
	
	/*HitBoxBrazier->SetGenerateOverlapEvents(false);
	HitBoxBrazier->SetRelativeLocation(HitBoxBrazier->GetRelativeLocation() - 1.f);*/
}




