// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiderWebActor.h"
//#include "MainCharacter.h"
#include "Components/BoxComponent.h"


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

	

	HitBoxWeb->OnComponentBeginOverlap.AddDynamic(this, &ASpiderWebActor::BeginOverlapWeb);
}

// Called when the game starts or when spawned
void ASpiderWebActor::BeginPlay()
{
	Super::BeginPlay();
	HitBoxWeb->SetGenerateOverlapEvents(false);
}

// Called every frame
void ASpiderWebActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ASpiderWebActor::BurnWeb() {
	//onoverlap true
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	UE_LOG(LogTemp, Warning, TEXT("Burn web"));

}

void ASpiderWebActor::BeginOverlapWeb(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Web detects %s"), *OtherActor->GetName());
	

	if (OtherActor->IsA(ASpiderWebActor::StaticClass()) && OtherActor != this) {
		ASpiderWebActor* SpiderWeb = Cast<ASpiderWebActor>(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Web detects %s"), *OtherActor->GetName());

		SpiderWeb->HitBoxWeb->SetGenerateOverlapEvents(true);
		SpiderWeb->HitBoxWeb->SetRelativeLocation(SpiderWeb->HitBoxWeb->GetRelativeLocation() + 1.f);
		BurnWeb();
	}
	
	HitBoxWeb->SetRelativeLocation(HitBoxWeb->GetRelativeLocation() - 1.f);
	HitBoxWeb->SetGenerateOverlapEvents(false);
}


