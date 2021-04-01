// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemActor.h"
#include "TorchActor.generated.h"

class UPointLightComponent;

UCLASS()
class PUPQUEST_API ATorchActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:

	ATorchActor();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bools")
	bool bTorchLit = true;

	UFUNCTION()
		void StartTorchFlame();
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* LightSorce {nullptr};
	
protected:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;

	virtual void BeginPlay() override;
};
