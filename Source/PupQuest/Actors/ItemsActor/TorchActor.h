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
	bool bTorchLit = false;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* Flame {nullptr};

	UFUNCTION()
		void TorchFlameOn();

	UFUNCTION()
		void TorchFlameOff();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;

protected:


	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* LightSorce {nullptr};
};
