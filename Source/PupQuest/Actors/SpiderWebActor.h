// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpiderWebActor.generated.h"

class UBoxComponent;
class AMainCharacter;
class UPointLightComponent;


UCLASS()
class PUPQUEST_API ASpiderWebActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpiderWebActor();

	UFUNCTION()
		void StartBurnWeb();

	UPROPERTY(EditAnywhere)
		UBoxComponent* HitBoxWeb {	nullptr };

	bool bBurning = false;

	void EndBurnWeb(); 

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* BurnWeb;

private:

	UFUNCTION()
		void BeginOverlapWeb(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle TimeGone;

	//FVector Scale = FVector(1.f);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
		UPointLightComponent* LightSorce { nullptr };

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* Flame { nullptr };
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
