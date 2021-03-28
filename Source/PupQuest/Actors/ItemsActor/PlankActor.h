// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemActor.h"
#include "PlankActor.generated.h"

UCLASS()
class PUPQUEST_API APlankActor : public ABaseItemActor
{
	GENERATED_BODY()
	
public:

	APlankActor();

protected:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
