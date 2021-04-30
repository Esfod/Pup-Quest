// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemActor.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "TorchActor.generated.h"

class UPointLightComponent;

UCLASS()
class PUPQUEST_API ATorchActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:

	ATorchActor();
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Bools")
	bool bTorchActorLit;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* Flame {nullptr};

	UFUNCTION()
		void TorchFlameOn();

	UFUNCTION()
		void TorchFlameOff();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* LightTorchSound;

protected:


	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* LightSorce {nullptr};
};
