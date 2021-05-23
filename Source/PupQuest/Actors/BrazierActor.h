// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "BrazierActor.generated.h"

class UPointLightComponent;

UCLASS()
class PUPQUEST_API ABrazierActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrazierActor();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Bools")
	bool bBrazierLit = false; 

	UPROPERTY(VisibleAnywhere)
		UPointLightComponent* BrazierLightSource { nullptr };

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* BrazierFlame { nullptr };

	UFUNCTION()
		void BrazierFlameOn();

	UFUNCTION()
		void BrazierFlameOff();

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* BurningSound;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshComp;
};
