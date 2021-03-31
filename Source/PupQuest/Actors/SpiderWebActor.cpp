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
	HitBoxWeb->SetGenerateOverlapEvents(false);


	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	

	HitBoxWeb->OnComponentBeginOverlap.AddDynamic(this, &ASpiderWebActor::BeginOverlapWeb);
}

// Called when the game starts or when spawned
void ASpiderWebActor::BeginPlay()
{
	Super::BeginPlay();
	
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
	/*FVector Move = HitBoxWeb->GetComponentLocation() += FVector(0.f, -100.f, 0.f);*/
	//HitBoxWeb->SetLocation(Move);


	UE_LOG(LogTemp, Warning, TEXT("Web detects %s"), *OtherActor->GetName());
	

	if (OtherActor->IsA(ASpiderWebActor::StaticClass())) {//&&OtherActor != this for å ikke telle med seg selv
		ASpiderWebActor* SpiderWeb = Cast<ASpiderWebActor>(OtherActor);
		SpiderWeb->BurnWeb();
		UE_LOG(LogTemp, Warning, TEXT("Web"));
	}

	/*if (OtherActor->IsA(AMainCharacter::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("character"));
	}*/
	//HitBoxWeb->GetComponentLocation() += FVector(0.f, 100.f, 0.f);
	HitBoxWeb->SetGenerateOverlapEvents(false);
}

//onoverlap function

//if other actor web
//burnweb()

