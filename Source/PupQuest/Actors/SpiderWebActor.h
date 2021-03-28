// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpiderWebActor.generated.h"

class UBoxComponent;

UCLASS()
class PUPQUEST_API ASpiderWebActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpiderWebActor();

	UFUNCTION()
		void BurnWeb();

	UPROPERTY(EditAnywhere)
		UBoxComponent* HitBoxWeb {	nullptr };

	

private:

	UFUNCTION()
		void BeginOverlapWeb(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
